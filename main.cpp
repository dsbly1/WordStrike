#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <memory>

#include "Game.h"
#include "FeedbackRenderer.h"
#include "WordRepository.h"
#include "Player.h"
#include "SessionManager.h"
#include "EasyMode.h"
#include "MediumMode.h"
#include "HardMode.h"

// Factory Method — returns a unique_ptr<DifficultyStrategy>
// Invalid choice throws std::invalid_argument caught in main()
std::unique_ptr<DifficultyStrategy> createStrategy(int choice) {
    switch (choice) {
        case 1: return std::make_unique<EasyMode>();
        case 2: return std::make_unique<MediumMode>();
        case 3: return std::make_unique<HardMode>();
        default: throw std::invalid_argument("Invalid difficulty choice.");
    }
}

int main() {
    FeedbackRenderer renderer;
    renderer.displayWelcome();

    // ── Load word bank ────────────────────────────────────────────────────
    WordRepository repo;
    try {
        repo.loadWords("words.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "[!] " << e.what() << "\n";
        std::cerr << "[!] Falling back to built-in word list.\n\n";
        // Hard-coded fallback word list
        std::ofstream fallback("words.txt");
        fallback << "crane\noaken\nphase\ntable\nblaze\nshard\nglyph\nscowl\nbrisk\nflute\n";
        fallback.close();
        try { repo.loadWords("words.txt"); }
        catch (...) { std::cerr << "Fatal: could not load fallback words.\n"; return 1; }
    }

    Player player;
    bool playAgain = true;

    while (playAgain) {
        // ── Difficulty selection ──────────────────────────────────────────
        renderer.displayDifficultyMenu();

        int choice = 0;
        std::cin >> choice;
        std::cin.ignore();

        std::unique_ptr<DifficultyStrategy> strategy;
        try {
            strategy = createStrategy(choice);
        } catch (const std::invalid_argument& e) {
            std::cerr << "[!] " << e.what() << " Please enter 1, 2, or 3.\n";
            continue;
        }

        // ── Pick a secret word based on difficulty ────────────────────────
        int minLen, maxLen;
        strategy->getWordLengthRange(minLen, maxLen);

        std::string secretWord;
        try {
            secretWord = repo.getRandomWord(minLen, maxLen);
        } catch (const std::runtime_error& e) {
            std::cerr << "[!] " << e.what() << "\n";
            return 1;
        }

        // ── Set up game ───────────────────────────────────────────────────
        Game game(std::move(strategy));
        game.registerObserver(&renderer);  // Observer registered at startup
        game.startGame(secretWord);

        player.resetSession();

        int attemptsUsed = 0;

        // ── Main game loop ────────────────────────────────────────────────
        while (!game.isGameOver()) {
            std::cout << "> ";
            std::string input;
            std::getline(std::cin, input);

            // Normalize leading/trailing whitespace
            while (!input.empty() && std::isspace(static_cast<unsigned char>(input.front())))
                input.erase(input.begin());
            while (!input.empty() && std::isspace(static_cast<unsigned char>(input.back())))
                input.pop_back();

            if (input.empty()) {
                std::cout << "[!] Please enter a word.\n";
                continue;
            }

            // ── Iteration 2 — UC-4: hint command ─────────────────────────
            if (input == "hint") {
                std::string hint = game.requestHint();
                std::cout << hint << "\n";
                continue;
            }

            // ── Iteration 2: quit command ─────────────────────────────────
            if (input == "quit") {
                std::cout << "Quitting current round. The word was: " << secretWord << "\n";
                break;
            }

            // ── Process guess through guard chain ─────────────────────────
            auto feedback = game.checkGuess(input);

            if (feedback.empty()) continue;

            GuessResult firstResult = feedback[0].result;

            // Handle guard rejections (no attempt consumed)
            if (firstResult == GuessResult::INVALID_CHARS) {
                renderer.displayError(GuessResult::INVALID_CHARS);
                continue;
            }
            if (firstResult == GuessResult::INVALID_LENGTH) {
                renderer.displayError(GuessResult::INVALID_LENGTH);
                continue;
            }
            if (firstResult == GuessResult::DUPLICATE) {
                renderer.displayError(GuessResult::DUPLICATE, input);
                continue;
            }

            // Valid guess — show per-letter feedback
            renderer.displayGuessFeedback(feedback);
            ++attemptsUsed;

            if (!game.isGameOver()) {
                renderer.displayAttemptsLeft(game.getAttemptsLeft());
            }
        }

        // ── Round over ────────────────────────────────────────────────────
        if (game.isGameOver()) {
            bool won = game.getAttemptsLeft() >= 0;
            // Check if won: all letters were CORRECT on last guess
            // The observer already printed the win/loss message
            if (!won || game.getAttemptsLeft() == 0) {
                // Show the answer on loss
                // (win message was displayed by FeedbackRenderer via Observer)
            }
            std::cout << "The word was: " << secretWord << "\n";

            // Record in SessionManager
            Result r;
            r.word     = secretWord;
            r.attempts = attemptsUsed;
            r.won      = (game.getAttemptsLeft() > 0);
            SessionManager::getInstance().recordResult(r);
        }

        // ── Iteration 2 — UC-5: show session history option ───────────────
        std::cout << "\n[H] View session history  [P] Play again  [Q] Quit\n> ";
        std::string cmd;
        std::getline(std::cin, cmd);

        if (cmd == "H" || cmd == "h") {
            SessionManager::getInstance().displayHistory();
            std::cout << "Play again? [Y/N]\n> ";
            std::getline(std::cin, cmd);
            playAgain = (cmd == "Y" || cmd == "y");
        } else if (cmd == "P" || cmd == "p") {
            playAgain = true;
        } else {
            playAgain = false;
        }
    }

    std::cout << "\nThanks for playing WordStrike! Final session total: "
              << SessionManager::getInstance().getTotalRoundsPlayed()
              << " round(s).\n";

    return 0;
}
