#include "HintEngine.h"
#include <algorithm>

HintEngine::HintEngine(const std::string& secretWord)
    : secret(secretWord), hintsAllowed(0), hintsUsed(0) {}

void HintEngine::setHintsAllowed(int n) {
    hintsAllowed = n;
}

bool HintEngine::hasHintsLeft() const {
    return hintsUsed < hintsAllowed;
}

std::string HintEngine::revealLetter() {
    if (!hasHintsLeft()) {
        return "No hints remaining.";
    }

    // Find the next position not already revealed
    for (int i = 0; i < static_cast<int>(secret.size()); ++i) {
        bool alreadyRevealed = std::find(revealedPositions.begin(),
                                          revealedPositions.end(), i)
                               != revealedPositions.end();
        if (!alreadyRevealed) {
            revealedPositions.push_back(i);
            ++hintsUsed;
            std::string result = "Letter " + std::to_string(i + 1) +
                                 " is '" + secret[i] + "'.";
            return result;
        }
    }

    // All positions exhausted (sentinel)
    return "No hints remaining.";
}
