/***********************************************************************
 * COSC 438 DEA - OBJECT-ORIENTED DESIGN
 * https://ccis.ucourses.com/d2l/home/1053692
 * Course Project: Second Iteration of Development
 * Damon Bly
 * Columbia College
 * 6/21/2026
 ***********************************************************************/

#include "FeedbackRenderer.h"
#include <iostream>
#include <cctype>

void FeedbackRenderer::onStateChange(GameState s) {
    // Observer fires after all state mutations are complete (contract documented here)
    switch (s) {
        case GameState::WON:
            std::cout << "\n*** Congratulations! You guessed the word! ***\n";
            break;
        case GameState::LOST:
            std::cout << "\n*** Game over! Better luck next time. ***\n";
            break;
        case GameState::IN_PROGRESS:
            break;
    }
}

void FeedbackRenderer::displayGuessFeedback(const std::vector<LetterFeedback>& feedback) const {
    for (const auto& lf : feedback) {
        std::string label;
        switch (lf.result) {
            case GuessResult::CORRECT: label = "CORRECT"; break;
            case GuessResult::PARTIAL: label = "PARTIAL"; break;
            case GuessResult::WRONG:   label = "WRONG";   break;
            default: break;
        }
        std::cout << static_cast<char>(std::toupper(static_cast<unsigned char>(lf.letter)))
                  << " - " << label << "   ";
    }
    std::cout << "\n";
}

void FeedbackRenderer::displayError(GuessResult reason, const std::string& guess) const {
    switch (reason) {
        case GuessResult::DUPLICATE:
            std::cout << "[!] You already guessed '" << guess
                      << "'. Try a different word.\n";
            break;
        case GuessResult::INVALID_LENGTH:
            std::cout << "[!] Invalid length. Please enter the correct number of letters.\n";
            break;
        case GuessResult::INVALID_CHARS:
            std::cout << "[!] Invalid guess. Please enter alphabetic characters only.\n";
            break;
        default:
            break;
    }
}

void FeedbackRenderer::displayAttemptsLeft(int n) const {
    std::cout << "Attempts remaining: " << n << "\n";
}

void FeedbackRenderer::displayWelcome() const {
    std::cout << "==============================\n";
    std::cout << "    Welcome to WordStrike!    \n";
    std::cout << "==============================\n\n";
}

void FeedbackRenderer::displayDifficultyMenu() const {
    std::cout << "Select difficulty:\n";
    std::cout << "  1) Easy   (8 attempts, 3 hints, 4-5 letter words)\n";
    std::cout << "  2) Medium (6 attempts, 1 hint,  5-6 letter words)\n";
    std::cout << "  3) Hard   (4 attempts, 0 hints, 6-8 letter words)\n";
    std::cout << "> ";
}
