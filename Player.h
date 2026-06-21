/***********************************************************************
 * COSC 438 DEA - OBJECT-ORIENTED DESIGN
 * https://ccis.ucourses.com/d2l/home/1053692
 * Course Project: Second Iteration of Development
 * Damon Bly
 * Columbia College
 * 6/21/2026
 ***********************************************************************/

#pragma once
#include <string>
#include <vector>

class Player {
public:
    Player();

    // Normalizes to lowercase, records the guess, returns the normalized form
    std::string makeGuess(const std::string& input);

    // Returns true if this word has already been guessed this session
    bool hasGuessed(const std::string& word) const;

    int  getScore()  const;
    void addScore(int points);
    void resetSession();

private:
    std::vector<std::string> guessHistory;
    int score;
};
