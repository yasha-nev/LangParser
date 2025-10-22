#include "Render.hpp"

#include <iostream>

Render::Render(Vocabulary& vocabulary):
    m_vocabulary(vocabulary) {
}

void Render::renderLexem(const Lexem& lexem) {
    std::cout << formatLexem(lexem);
}

void Render::renderEarleyItem(const EarleyItem& eItem) {
    std::cout << formatEarlyItem(eItem);
}

static std::string category2String(LexemCategory lexemCategory) {
    switch(lexemCategory) {
        case LexemCategory::OPERATOR:
            return "OPERATOR";
        case LexemCategory::CONDITION:
            return "CONDITION";
        case LexemCategory::LOGIC:
            return "LOGIC";
        case LexemCategory::TYPES:
            return "TYPES";
        case LexemCategory::KEYWORD:
            return "KEYWORD";
        case LexemCategory::END:
            return "END";
        case LexemCategory::END_WORDS:
            return "END_WORDS";
        case LexemCategory::VALUE:
            return "VALUE";
        case LexemCategory::SPACE:
            return "SPACE";
        case LexemCategory::VARIABLES:
            return "VARIABLES";
        default:
            return "";
    }
}

std::string Render::formatLexem(const Lexem& lexem) const {
    std::stringstream ss;

    ss << "----Token-----\n";
    ss << "name: " << m_vocabulary.getWord(lexem.getWordId()).second << "\n";
    ss << "type: " << category2String(lexem.getType()) << "\n";
    ss << "id: " << lexem.getPosition() << "\n";
    ss << "--------------\n";

    return ss.str();
}

std::string Render::formatEarlyItem(const EarleyItem& eItem) const {
    std::stringstream ss;

    const std::string& vn = m_vocabulary.getWord(eItem.getVn()).second;
    const auto& rule = eItem.getRule();

    size_t n = vn.size();

    ss << vn << " -> ";

    for(const auto& part: rule) {
        const std::string& word = m_vocabulary.getWord(part).second;
        n += word.size() + 1;
        ss << word << " ";
    }

    ss << std::string(30 - n, ' ') << " | " << eItem.getNumber() << "\n";

    return ss.str();
}
