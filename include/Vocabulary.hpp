#pragma once

#include <LexemCategory.hpp>
#include <algorithm>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define COUNT_ID_IN_CATEGORY 100

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
    void addWord(LexemCategory category, const std::string& word) noexcept;

    /**
     * @brief Checks if a word belongs to a given category.
     * @param category Token category.
     * @param word Word string.
     * @return true if the word exists in the category.
     */
    bool contains(LexemCategory category, const std::string& word) const noexcept;

    /**
     * @brief get lexem type and string value by wordId
     * @param wordId word id in vocabulary
     * @return pair of Token category and string value
     */
    const std::pair<LexemCategory, std::string>& getWord(int wordId) const noexcept;

    /**
     * @brief get id of word from vocabulary
     * @param category - Token category
     * @param word - language word
     * @return word id
     */
    int getWordId(LexemCategory category, const std::string& word) const noexcept;

    /**
     * @brief Gets the position of a word in the given category.
     * @param category Token category.
     * @param word Word string.
     * @return Position index or -1 if not found.
     */
    int getWordPosition(LexemCategory category, const std::string& word) const noexcept;

    /**
     * @return List of category-pattern pairs.
     */
    const std::vector<std::pair<LexemCategory, std::regex>>& getPatterns() const noexcept;

private:
    /**
     * @brief Rebuilds regex pattern for the given category.
     * @param category Token category.
     */
    void rebuildPattern(LexemCategory category);

    std::unordered_map<LexemCategory, std::unordered_map<std::string, int>> m_words;

    std::unordered_map<int, std::pair<LexemCategory, std::string>> m_reverse;

    std::vector<std::pair<LexemCategory, std::regex>> m_patterns;
};
