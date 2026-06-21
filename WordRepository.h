#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class WordRepository {
public:
    // Loads words and hints from a pipe-delimited file: WORD|HINT
    // Falls back to words.txt if words_with_hints.txt is not found
    void loadWords(const std::string& filename);

    std::vector<std::string> filterByDifficulty(int minLen, int maxLen) const;

    // Returns a random word in the given length range
    std::string getRandomWord(int minLen, int maxLen) const;

    // Returns the hint for a given word, or empty string if none exists
    std::string getHintFor(const std::string& word) const;

    bool isValidWord(const std::string& word) const;

private:
    std::vector<std::string>              wordBank;
    std::unordered_map<std::string, std::string> hintMap;
};
