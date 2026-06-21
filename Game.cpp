#include "Game.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <iostream>

Game::Game(std::unique_ptr<DifficultyStrategy> strategy)
    : difficulty(std::move(strategy)),
      attemptsLeft(0), hintsLeft(0), gameOver(false)
{}

void Game::startGame(const std::string& word, const std::string& wordHint) {
    if (word.empty())
        throw std::invalid_argument("Secret word cannot be empty.");

    secretWord   = word;
    attemptsLeft = difficulty->getMaxAttempts();
    hintsLeft    = difficulty->getHintsAllowed();
    gameOver     = false;
    guessedWords.clear();

    difficulty->applyRules();

    // Display the word hint right after the word is chosen
    if (!wordHint.empty())
        std::cout << "HINT: " << wordHint << "\n";

    hintEngine = std::make_unique<HintEngine>(secretWord);
    hintEngine->setHintsAllowed(hintsLeft);

    std::cout << "Attempts remaining: " << attemptsLeft << "\n\n";
}

// Guard chain (priority order — only valid non-duplicate guesses consume an attempt):
//   1. INVALID_CHARS  — non-alphabetic input
//   2. INVALID_LENGTH — wrong word length
//   3. DUPLICATE      — already guessed this round
//   4. CORRECT / PARTIAL / WRONG — valid guess, consumes an attempt
std::vector<LetterFeedback> Game::checkGuess(const std::string& input) {
    std::vector<LetterFeedback> feedback;

    std::string guess = input;
    std::transform(guess.begin(), guess.end(), guess.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    // Guard 1: alphabetic check
    for (char c : guess) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            feedback.push_back({ '\0', GuessResult::INVALID_CHARS });
            return feedback;
        }
    }
    // Guard 2: length check
    if (guess.size() != secretWord.size()) {
        feedback.push_back({ '\0', GuessResult::INVALID_LENGTH });
        return feedback;
    }
    // Guard 3: duplicate check
    for (const auto& prev : guessedWords) {
        if (prev == guess) {
            feedback.push_back({ '\0', GuessResult::DUPLICATE });
            return feedback;
        }
    }

    // Valid guess — record and consume an attempt
    guessedWords.push_back(guess);
    --attemptsLeft;

    // Guard 4: evaluate per-letter
    for (size_t i = 0; i < guess.size(); ++i) {
        char c = guess[i];
        GuessResult result;
        if (c == secretWord[i])
            result = GuessResult::CORRECT;
        else if (secretWord.find(c) != std::string::npos)
            result = GuessResult::PARTIAL;
        else
            result = GuessResult::WRONG;
        feedback.push_back({ c, result });
    }

    // Check win condition
    bool allCorrect = true;
    for (const auto& lf : feedback)
        if (lf.result != GuessResult::CORRECT) { allCorrect = false; break; }

    // All state mutations complete; notify observers after
    if (allCorrect) {
        gameOver = true;
        notifyObservers(GameState::WON);
    } else if (attemptsLeft == 0) {
        gameOver = true;
        notifyObservers(GameState::LOST);
    } else {
        notifyObservers(GameState::IN_PROGRESS);
    }

    return feedback;
}

void Game::endGame(bool playerWon) {
    gameOver = true;
    notifyObservers(playerWon ? GameState::WON : GameState::LOST);
}

std::string Game::requestHint() {
    if (!hintEngine) return "No hint available.";
    return hintEngine->revealLetter();
}

bool Game::isGameOver()      const { return gameOver; }
int  Game::getAttemptsLeft() const { return attemptsLeft; }
int  Game::getWordLength()   const { return static_cast<int>(secretWord.size()); }

void Game::registerObserver(IObserver* obs) {
    if (obs) observers.push_back(obs);
}
void Game::removeObserver(IObserver* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

// Contract: all state mutations must complete before notifyObservers() fires
void Game::notifyObservers(GameState state) {
    for (auto* obs : observers)
        obs->onStateChange(state);
}
