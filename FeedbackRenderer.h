/***********************************************************************
 * COSC 438 DEA - OBJECT-ORIENTED DESIGN
 * https://ccis.ucourses.com/d2l/home/1053692
 * Course Project: Second Iteration of Development
 * Damon Bly
 * Columbia College
 * 6/21/2026
 ***********************************************************************/

#pragma once
#include "IObserver.h"
#include <string>
#include <vector>

enum class GuessResult {
    CORRECT,
    PARTIAL,
    WRONG,
    DUPLICATE,
    INVALID_LENGTH,
    INVALID_CHARS
};

struct LetterFeedback {
    char        letter;
    GuessResult result;
};

class FeedbackRenderer : public IObserver {
public:
    // Called by Game after all state mutations are complete (Observer contract)
    void onStateChange(GameState s) override;

    // Displays per-letter feedback after each guess
    void displayGuessFeedback(const std::vector<LetterFeedback>& feedback) const;

    // Displays error messages for invalid/duplicate guesses
    void displayError(GuessResult reason, const std::string& guess = "") const;

    void displayAttemptsLeft(int n) const;
    void displayWelcome() const;
    void displayDifficultyMenu() const;
};
