/***********************************************************************
 * COSC 438 DEA - OBJECT-ORIENTED DESIGN
 * https://ccis.ucourses.com/d2l/home/1053692
 * Course Project: Second Iteration of Development
 * Damon Bly
 * Columbia College
 * 6/21/2026
 ***********************************************************************/

#include "Player.h"
#include <algorithm>
#include <cctype>

Player::Player() : score(0) {}

std::string Player::makeGuess(const std::string& input) {
    std::string normalized = input;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    guessHistory.push_back(normalized);
    return normalized;
}

bool Player::hasGuessed(const std::string& word) const {
    std::string lower = word;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    for (const auto& g : guessHistory) {
        if (g == lower) return true;
    }
    return false;
}

int Player::getScore() const { return score; }

void Player::addScore(int points) { score += points; }

void Player::resetSession() {
    guessHistory.clear();
    score = 0;
}
