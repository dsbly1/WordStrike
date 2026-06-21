/***********************************************************************
 * COSC 438 DEA - OBJECT-ORIENTED DESIGN
 * https://ccis.ucourses.com/d2l/home/1053692
 * Course Project: Second Iteration of Development
 * Damon Bly
 * Columbia College
 * 6/21/2026
 ***********************************************************************/

#pragma once

// Abstract base class — Template Method pattern
// applyRules() defines the algorithm skeleton; subclasses supply values.
class DifficultyStrategy {
public:
    virtual void applyRules() = 0;
    virtual int  getMaxAttempts()  const = 0;
    virtual int  getHintsAllowed() const = 0;
    virtual void getWordLengthRange(int& min, int& max) const = 0;
    virtual ~DifficultyStrategy() = default;
};
