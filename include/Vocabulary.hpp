#pragma once

#include "nlohmann/json.hpp"

#include <LexemCategory.hpp>
#include <algorithm>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Vocabulary {
public:
    void loadFromJson(const std::string& filePath);

    void addWord(LexemCategory category, const std::string& word);

    void addWords(LexemCategory category, std::initializer_list<std::string> wordList);

    bool contains(LexemCategory category, const std::string& word) const;

    int getWordPosition(LexemCategory category, const std::string& word) const;

    std::vector<std::string> getWords(LexemCategory category) const;

    const std::vector<std::pair<LexemCategory, std::regex>>& getPatterns() const;

private:
    void rebuildPattern(LexemCategory category);

    std::unordered_map<LexemCategory, std::unordered_set<std::string>> m_words;

    std::vector<std::pair<LexemCategory, std::regex>> m_patterns;
};
