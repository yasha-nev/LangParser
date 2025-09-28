#include "Vocabulary.hpp"

#include <iostream>

static LexemCategory string2LexemCategory(const std::string& str) {
    if(str == "OPERATOR") {
        return LexemCategory::OPERATOR;
    } else if(str == "CONDITION") {
        return LexemCategory::CONDITION;
    } else if(str == "LOGIC") {
        return LexemCategory::LOGIC;
    } else if(str == "TYPES") {
        return LexemCategory::TYPES;
    } else if(str == "KEYWORD") {
        return LexemCategory::KEYWORD;
    } else if(str == "END") {
        return LexemCategory::END;
    } else if(str == "VARIABLES") {
        return LexemCategory::VARIABLES;
    } else if(str == "VALUE") {
        return LexemCategory::VALUE;
    } else if(str == "SPACE") {
        return LexemCategory::SPACE;
    } else {
        return LexemCategory::SPACE;
    }
}

void Vocabulary::loadFromJson(const std::string& filePath) {
    std::ifstream file(filePath);
    using json = nlohmann::json;

    json j;
    file >> j;

    for(auto& it: j["vocabulary"].items()) {
        const std::string& lhs = it.key();
        LexemCategory category = string2LexemCategory(lhs);
        for(auto& word: it.value()) {
            addWord(category, word.get<std::string>());
        }
    }
    file.close();
}

void Vocabulary::addWord(LexemCategory category, const std::string& word) {
    m_words[category].insert(word);
    rebuildPattern(category);
}

void Vocabulary::addWords(LexemCategory category, std::initializer_list<std::string> wordList) {
    m_words[category].insert(wordList);
    rebuildPattern(category);
}

bool Vocabulary::contains(LexemCategory category, const std::string& word) const {
    auto it = m_words.find(category);
    return it != m_words.end() && it->second.count(word) > 0;
}

static std::string removeSlash(const std::string& input) {
    std::string result = input;
    size_t pos = result.find('\\');
    if(pos != std::string::npos) {
        result.erase(pos, 1);
    }
    return result;
}

int Vocabulary::getWordPosition(LexemCategory category, const std::string& word) const {
    auto words = getWords(category);
    for(size_t i = 0; i < words.size(); i++) {
        if(removeSlash(words[i]) == word) {
            return i;
        }
    }

    return -1;
}

std::vector<std::string> Vocabulary::getWords(LexemCategory category) const {
    std::vector<std::string> result;
    auto it = m_words.find(category);
    if(it != m_words.end()) {
        result.insert(result.end(), it->second.begin(), it->second.end());
    }
    return result;
}

const std::vector<std::pair<LexemCategory, std::regex>>& Vocabulary::getPatterns() const {
    return m_patterns;
}

void Vocabulary::rebuildPattern(LexemCategory category) {
    auto it = m_words.find(category);
    if(it == m_words.end() || it->second.empty()) {
        return;
    }

    const auto& words = it->second;

    std::string pattern = "^(";
    bool first = true;
    for(auto& word: words) {
        if(!first) {
            pattern += "|";
        }
        pattern += word;
        first = false;
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
