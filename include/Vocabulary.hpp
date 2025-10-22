#pragma once

#include <LexemCategory.hpp>
#include <algorithm>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * @class Vocabulary
 * @brief Stores and manages the vocabulary of tokens.
 */
class Vocabulary {
public:
    /**
     * @brief Adds a word to the vocabulary.
     * @param category Token category.
     * @param word Word string.
     */
    void addWord(LexemCategory category, const std::string& word);

    /**
     * @brief Adds multiple words to the vocabulary.
     * @param category Token category.
     * @param wordList List of words.
     */
    void addWords(LexemCategory category, std::initializer_list<std::string> wordList);

    /**
     * @brief Checks if a word belongs to a given category.
     * @param category Token category.
     * @param word Word string.
     * @return true if the word exists in the category.
     */
    bool contains(LexemCategory category, const std::string& word) const;

    /**
     * @brief Gets the position of a word in the given category.
     * @param category Token category.
     * @param word Word string.
     * @return Position index or -1 if not found.
     */
    int getWordPosition(LexemCategory category, const std::string& word) const;

    /**
     * @brief Retrieves all words of the given category.
     * @param category Token category.
     * @return List of words.
     */
    std::vector<std::string> getWords(LexemCategory category) const;

    /**
     * @return List of category-pattern pairs.
     */
    const std::vector<std::pair<LexemCategory, std::regex>>& getPatterns() const;

private:
    /**
     * @brief Rebuilds regex pattern for the given category.
     * @param category Token category.
     */
    void rebuildPattern(LexemCategory category);

    std::unordered_map<LexemCategory, std::unordered_map<std::string, int>> m_words;

    std::unordered_map<LexemCategory, std::unordered_map<int, std::string>> m_reverse;

    std::vector<std::pair<LexemCategory, std::regex>> m_patterns;
};
