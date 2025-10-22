#include "Vocabulary.hpp"

#include <iostream>

void Vocabulary::addWord(LexemCategory category, const std::string& word) noexcept {
    int wordId = static_cast<int>(category) * COUNT_ID_IN_CATEGORY + m_words[category].size();

    m_words[category][word] = wordId;
    m_reverse[wordId] = std::pair<LexemCategory, std::string>(category, word);

    rebuildPattern(category);
}

bool Vocabulary::contains(LexemCategory category, const std::string& word) const noexcept {
    auto it = m_words.find(category);
    return it != m_words.end() && it->second.count(word) > 0;
}

const std::pair<LexemCategory, std::string>& Vocabulary::getWord(int wordId) const noexcept {
    auto it = m_reverse.find(wordId);
    if(it != m_reverse.end()) {
        return (*it).second;
    } else {
        static auto defaultValue = std::pair<LexemCategory, std::string>(
            LexemCategory::NOCATEGORY, "");
        return defaultValue;
    }
}

int Vocabulary::getWordId(LexemCategory category, const std::string& word) const noexcept {
    auto it = m_words.find(category);

    if(it != m_words.end()) {
        auto it2 = (*it).second.find(word);

        return (it2 != (*it).second.end()) ? (*it2).second : -1;
    }

    return -1;
}

int Vocabulary::getWordId(const std::string& word) const noexcept {
    for(const auto& [category, words]: m_words) {
        auto it = words.find(word);
        if(it != words.end()) {
            return (*it).second;
        }
    }

    return -1;
}

int Vocabulary::getWordPosition(LexemCategory category, const std::string& word) const noexcept {
    auto wordId = getWordId(category, word);

    if(wordId != -1) {
        return wordId - static_cast<int>(category) * COUNT_ID_IN_CATEGORY;
    }

    return -1;
}

const std::vector<std::pair<LexemCategory, std::regex>>& Vocabulary::getPatterns() const noexcept {
    return m_patterns;
}

void Vocabulary::rebuildPattern(LexemCategory category) {
    auto it = m_words.find(category);
    if(it == m_words.end() || it->second.empty()) {
        return;
    }

    const auto& words = it->second;

    static std::vector<std::string> re_exceptons = { "+", "*", "{", "}", "(", ")", "[", "]" };

    std::string pattern = "^(";
    bool isFirst = true;
    for(const auto& [word, wordId]: words) {
        if(!isFirst) {
            pattern += "|";
        }

        if(std::find(re_exceptons.cbegin(), re_exceptons.cend(), word) != re_exceptons.cend()) {
            pattern += "\\" + word;
        } else {
            pattern += word;
        }
        isFirst = false;
    }

    pattern += ")";

    std::regex regexPattern(pattern);

    for(auto& kv: m_patterns) {
        if(kv.first == category) {
            kv.second = std::move(regexPattern);
            return;
        }
    }

    m_patterns.push_back(std::make_pair(category, std::move(regexPattern)));
}
