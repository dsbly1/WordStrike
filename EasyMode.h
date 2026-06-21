#pragma once
#include "DifficultyStrategy.h"

class EasyMode : public DifficultyStrategy {
public:
    void applyRules() override;
    int  getMaxAttempts()  const override;
    int  getHintsAllowed() const override;
    void getWordLengthRange(int& min, int& max) const override;
};
