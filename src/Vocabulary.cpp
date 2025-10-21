#include "Vocabulary.hpp"

#include <iostream>

static std::string removeSlash(const std::string& input) {
    std::string result = input;
    size_t pos = result.find('\\');
    if(pos != std::string::npos) {
        result.erase(pos, 1);
    }
    return result;
}

void Vocabulary::addWord(LexemCategory category, const std::string& word) {
    if (contains(category, word))
        return;

    int id = m_nextId++;
    m_words[category][word] = id;
    m_reverse[id] = { category, word };

    rebuildPattern(category);
}

bool Vocabulary::contains(LexemCategory category, const std::string& word) const {
    auto it = m_words.find(category);
    return it != m_words.end() && it->second.find(word) != it->second.end();
}

int Vocabulary::getWordId(LexemCategory category, const std::string& word) const {
    auto catIt = m_words.find(category);
    if (catIt == m_words.end())
        return -1;

    auto wordIt = catIt->second.find(word);
    return (wordIt != catIt->second.end()) ? wordIt->second : -1;
}

int Vocabulary::getWordId(const std::string& word) const {
    for (const auto& [cat, words] : m_words) {
        auto it = words.find(word);
        if (it != words.end())
            return it->second;
    }
    return -1;
}

std::string Vocabulary::getWord(int id) const {
    auto it = m_reverse.find(id);
    return (it != m_reverse.end()) ? it->second.second : "";
}

std::string Vocabulary::getWord(LexemCategory category, int id) const {
    auto it = m_reverse.find(id);
    if (it != m_reverse.end() && it->second.first == category)
        return it->second.second;
    return "";
}

int Vocabulary::getWordPosition(LexemCategory category, const std::string& word) const {
    int position = -1;
    
    auto categoryIt = m_words.find(category);
    if(categoryIt != m_words.end()) {
        auto word_it = categoryIt->second.find(word);
        if(word_it != categoryIt->second.end()) {
            position = word_it->second;
        }
    }
    
    if(position != -1) {
        return position - static_cast<int>(category) * 100;
    }
    
    return position;
 }


void Vocabulary::rebuildPattern(LexemCategory category) {
    const auto& words = m_words[category];
    if (words.empty())
        return;

    std::string pattern = "^(";
    bool first = true;
    for (const auto& [word, _] : words) {
        if (!first) pattern += "|";
        pattern += word;
        first = false;
    }
    pattern += ")";

    std::regex re(pattern);
    m_categoryRegex[category] = re;

    // обновляем общий кэш
    m_patterns.clear();
    for (const auto& [cat, regex] : m_categoryRegex) {
        m_patterns.emplace_back(cat, regex);
    }
}

const std::vector<std::pair<LexemCategory, std::regex>>& Vocabulary::getPatterns() {
    return m_patterns;
}
