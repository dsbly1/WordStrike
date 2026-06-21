/***********************************************************************
 * COSC 438 DEA - OBJECT-ORIENTED DESIGN
 * https://ccis.ucourses.com/d2l/home/1053692
 * Course Project: Second Iteration of Development
 * Damon Bly
 * Columbia College
 * 6/21/2026
 ***********************************************************************/

#pragma once
#include "DifficultyStrategy.h"

class HardMode : public DifficultyStrategy {
public:
    void applyRules() override;
    int  getMaxAttempts()  const override;
    int  getHintsAllowed() const override;
    void getWordLengthRange(int& min, int& max) const override;
};
