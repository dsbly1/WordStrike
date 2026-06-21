/***********************************************************************
 * COSC 438 DEA - OBJECT-ORIENTED DESIGN
 * https://ccis.ucourses.com/d2l/home/1053692
 * Course Project: Second Iteration of Development
 * Damon Bly
 * Columbia College
 * 6/21/2026
 ***********************************************************************/

#pragma once
#include <string>
#include <vector>

struct Result {
    std::string word;
    int  attempts;
    bool won;
};

// Meyers Singleton — thread-safe, no explicit locking required
class SessionManager {
public:
    static SessionManager& getInstance();

    // Validates the Result before appending; malformed entries are discarded
    void recordResult(const Result& r);

    // Iteration 2: displays full session history (UC-5)
    void displayHistory() const;

    int getTotalRoundsPlayed() const;

private:
    SessionManager() = default;
    ~SessionManager() = default;
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;

    std::vector<Result> history;
};
