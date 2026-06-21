/***********************************************************************
 * COSC 438 DEA - OBJECT-ORIENTED DESIGN
 * https://ccis.ucourses.com/d2l/home/1053692
 * Course Project: Second Iteration of Development
 * Damon Bly
 * Columbia College
 * 6/21/2026
 ***********************************************************************/

#include "MediumMode.h"
#include <iostream>

// Medium: 6 attempts, 1 hint, 5-6 letter words
void MediumMode::applyRules() {
    int min, max;
    getWordLengthRange(min, max);
    std::cout << "Medium mode selected. Good luck!\n";
    std::cout << "A " << min << "-" << max << " letter word has been chosen.\n";
    std::cout << "Hints available: " << getHintsAllowed() << " (type 'hint' to reveal a letter)\n";
}

int MediumMode::getMaxAttempts()  const { return 6; }
int MediumMode::getHintsAllowed() const { return 1; }

void MediumMode::getWordLengthRange(int& min, int& max) const {
    min = 5;
    max = 6;
}
