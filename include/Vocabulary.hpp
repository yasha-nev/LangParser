#pragma once

#include <LexemCategory.hpp>
#include <algorithm>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Vocabulary {
public:
    void addWord(LexemCategory category, const std::string& word);

    bool contains(LexemCategory category, const std::string& word) const;

    int getWordId(LexemCategory category, const std::string& word) const;
    int getWordId(const std::string& word) const;

    std::string getWord(int id) const;
    std::string getWord(LexemCategory category, int id) const;

    int getWordPosition(LexemCategory category, const std::string& word) const;

    const std::vector<std::pair<LexemCategory, std::regex>>& getPatterns();

private:
    void rebuildPattern(LexemCategory category);

    // Для быстрого поиска: category → word → id
    std::unordered_map<LexemCategory, std::unordered_map<std::string, int>> m_words;

    // Для обратного поиска: id → (category, word)
    std::unordered_map<int, std::pair<LexemCategory, std::string>> m_reverse;

    // Regex для токенизации
    std::unordered_map<LexemCategory, std::regex> m_categoryRegex;

    // Счётчик уникальных ID
    int m_nextId = 0;

    // Кэш паттернов
    std::vector<std::pair<LexemCategory, std::regex>> m_patterns;
};
