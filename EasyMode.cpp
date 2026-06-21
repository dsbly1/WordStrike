#include "EasyMode.h"
#include <iostream>

// Easy: 8 attempts, 3 hints, 4-5 letter words
void EasyMode::applyRules() {
    int min, max;
    getWordLengthRange(min, max);
    std::cout << "Easy mode selected. Good luck!\n";
    std::cout << "A " << min << "-" << max << " letter word has been chosen.\n";
    std::cout << "Hints available: " << getHintsAllowed() << " (type 'hint' to reveal a letter)\n";
}

int EasyMode::getMaxAttempts() const  { return 8; }
int EasyMode::getHintsAllowed() const { return 3; }

void EasyMode::getWordLengthRange(int& min, int& max) const {
    min = 4;
    max = 5;
}
