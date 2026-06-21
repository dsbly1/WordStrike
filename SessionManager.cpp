#include "SessionManager.h"
#include <iostream>

SessionManager& SessionManager::getInstance() {
    static SessionManager instance; // Meyers Singleton — initialized exactly once
    return instance;
}

void SessionManager::recordResult(const Result& r) {
    // Validate before appending; malformed entries discarded to std::cerr
    if (r.word.empty() || r.attempts <= 0) {
        std::cerr << "[SessionManager] Discarded malformed result.\n";
        return;
    }
    history.push_back(r);
}

// Iteration 2 — UC-5: full session history display
void SessionManager::displayHistory() const {
    if (history.empty()) {
        std::cout << "No rounds played this session.\n";
        return;
    }
    std::cout << "\n===== Session History =====\n";
    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << "Round " << (i + 1) << ": "
                  << history[i].word << " | "
                  << history[i].attempts << " attempt(s) | "
                  << (history[i].won ? "WIN" : "LOSS") << "\n";
    }
    std::cout << "===========================\n";
}

int SessionManager::getTotalRoundsPlayed() const {
    return static_cast<int>(history.size());
}
