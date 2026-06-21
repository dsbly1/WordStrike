#pragma once
#include <string>
#include <vector>

class WordRepository {
public:
    // Throws std::runtime_error if file is missing or empty after filtering
    void loadWords(const std::string& filename);

    // Returns words matching the given length range
    std::vector<std::string> filterByDifficulty(int minLen, int maxLen) const;

    // Returns a random word from the filtered list
    // Throws std::runtime_error if the filtered list is empty
    std::string getRandomWord(int minLen, int maxLen) const;

    // Returns true if the word exists in the full word bank
    bool isValidWord(const std::string& word) const;

private:
    std::vector<std::string> wordBank;
};
