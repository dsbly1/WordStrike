#include "HardMode.h"
#include <iostream>

// Hard: 4 attempts, 0 hints, 6-8 letter words
void HardMode::applyRules() {
    int min, max;
    getWordLengthRange(min, max);
    std::cout << "Hard mode selected. Good luck!\n";
    std::cout << "A " << min << "-" << max << " letter word has been chosen.\n";
    std::cout << "Hints available: " << getHintsAllowed() << " (type 'hint' to reveal a letter)\n";
}

int HardMode::getMaxAttempts()  const { return 4; }
int HardMode::getHintsAllowed() const { return 0; }

void HardMode::getWordLengthRange(int& min, int& max) const {
    min = 6;
    max = 8;
}
