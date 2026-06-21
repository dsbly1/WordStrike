#include "WordRepository.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>

static bool isAllAlpha(const std::string& w) {
    for (char c : w)
        if (!std::isalpha(static_cast<unsigned char>(c))) return false;
    return !w.empty();
}

static std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

void WordRepository::loadWords(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open word file: " + filename);

    wordBank.clear();
    hintMap.clear();

    std::string line;
    while (std::getline(file, line)) {
        // Skip comments and blank lines
        if (line.empty() || line[0] == '#') continue;

        // Trim trailing whitespace
        while (!line.empty() && std::isspace(static_cast<unsigned char>(line.back())))
            line.pop_back();

        // Check for WORD|HINT format
        auto pipe = line.find('|');
        std::string word, hint;
        if (pipe != std::string::npos) {
            word = line.substr(0, pipe);
            hint = line.substr(pipe + 1);
        } else {
            word = line;
        }

        // Trim word
        while (!word.empty() && std::isspace(static_cast<unsigned char>(word.back())))
            word.pop_back();

        if (!isAllAlpha(word)) continue;

        word = toLower(word);
        wordBank.push_back(word);
        if (!hint.empty())
            hintMap[word] = hint;
    }

    if (wordBank.empty())
        throw std::runtime_error("Word file is empty or contains no valid words: " + filename);
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
    if (filtered.empty())
        throw std::runtime_error("No words found in the requested length range.");
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    return filtered[std::rand() % filtered.size()];
}

std::string WordRepository::getHintFor(const std::string& word) const {
    auto it = hintMap.find(toLower(word));
    if (it != hintMap.end()) return it->second;
    return "";
}

bool WordRepository::isValidWord(const std::string& word) const {
    std::string lower = toLower(word);
    for (const auto& w : wordBank)
        if (w == lower) return true;
    return false;
}
