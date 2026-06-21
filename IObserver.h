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
