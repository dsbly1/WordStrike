#pragma once
#include "IObserver.h"
#include "FeedbackRenderer.h"
#include "DifficultyStrategy.h"
#include "HintEngine.h"
#include <string>
#include <vector>
#include <memory>

class Game {
public:
    explicit Game(std::unique_ptr<DifficultyStrategy> strategy);

    void startGame(const std::string& secretWord);

    // Guard chain: INVALID_CHARS -> INVALID_LENGTH -> DUPLICATE -> CORRECT/PARTIAL/WRONG
    // Only valid, non-duplicate guesses consume an attempt.
    std::vector<LetterFeedback> checkGuess(const std::string& input);

    void endGame(bool playerWon);

    // Iteration 2 — UC-4: request a hint via HintEngine
    std::string requestHint();

    bool isGameOver()     const;
    int  getAttemptsLeft() const;
    int  getWordLength()   const;

    void registerObserver(IObserver* obs);
    void removeObserver(IObserver* obs);

private:
    void notifyObservers(GameState state);

    std::unique_ptr<DifficultyStrategy> difficulty; // RAII ownership via unique_ptr
    std::vector<IObserver*>             observers;
    std::unique_ptr<HintEngine>         hintEngine;

    std::string secretWord;
    int  attemptsLeft;
    int  hintsLeft;
    bool gameOver;

    // Tracks guesses this round for duplicate detection
    std::vector<std::string> guessedWords;
};
