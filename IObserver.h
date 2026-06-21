/***********************************************************************
 * COSC 438 DEA - OBJECT-ORIENTED DESIGN
 * https://ccis.ucourses.com/d2l/home/1053692
 * Course Project: Second Iteration of Development
 * Damon Bly
 * Columbia College
 * 6/21/2026
 ***********************************************************************/

#pragma once

enum class GameState {
    IN_PROGRESS,
    WON,
    LOST
};

class IObserver {
public:
    virtual void onStateChange(GameState s) = 0;
    virtual ~IObserver() = default;
};
