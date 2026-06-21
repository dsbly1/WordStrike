#pragma once
#include <string>
#include <vector>

class HintEngine {
public:
    explicit HintEngine(const std::string& secretWord);

    // Reveals the next unrevealed letter position.
    // Returns "No hints remaining." when all positions are exhausted.
    std::string revealLetter();

    bool hasHintsLeft() const;
    void setHintsAllowed(int n);

private:
    std::string secret;
    std::vector<int> revealedPositions;
    int hintsAllowed;
    int hintsUsed;
};
