#include "WordRepository.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Validates that a word contains only alphabetic characters
static bool isAllAlpha(const std::string& w) {
    for (char c : w) {
        if (!std::isalpha(static_cast<unsigned char>(c))) return false;
    }
    return !w.empty();
}

void WordRepository::loadWords(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open word file: " + filename);
    }

    wordBank.clear();
    std::string line;
    while (std::getline(file, line)) {
        // Trim whitespace
        while (!line.empty() && std::isspace(static_cast<unsigned char>(line.back())))
            line.pop_back();
        while (!line.empty() && std::isspace(static_cast<unsigned char>(line.front())))
            line.erase(line.begin());

        if (!isAllAlpha(line)) continue;

        // Normalize to lowercase
        std::transform(line.begin(), line.end(), line.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        wordBank.push_back(line);
    }

    if (wordBank.empty()) {
        throw std::runtime_error("Word file is empty or contains no valid words: " + filename);
    }
}

std::vector<std::string> WordRepository::filterByDifficulty(int minLen, int maxLen) const {
    std::vector<std::string> filtered;
    for (const auto& w : wordBank) {
        int len = static_cast<int>(w.size());
        if (len >= minLen && len <= maxLen)
            filtered.push_back(w);
    }
    return filtered;
}

std::string WordRepository::getRandomWord(int minLen, int maxLen) const {
    auto filtered = filterByDifficulty(minLen, maxLen);
    if (filtered.empty()) {
        throw std::runtime_error("No words found in the requested length range.");
    }
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    return filtered[std::rand() % filtered.size()];
}

bool WordRepository::isValidWord(const std::string& word) const {
    std::string lower = word;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    for (const auto& w : wordBank) {
        if (w == lower) return true;
    }
    return false;
}
