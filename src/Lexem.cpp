#include "Lexem.hpp"

Lexem::Lexem(LexemCategory type, int wordId, int position, int lineNumber) :
    m_type(type),
    m_wordId(wordId),
    m_position(position),
    m_lineNumber(lineNumber) {
}

LexemCategory Lexem::getType() const {
    return m_type;
}

int Lexem::getWordId() const {
    return m_wordId;
}

int Lexem::getPosition() const {
    return m_position;
}

int Lexem::getLineNumber() const {
    return m_lineNumber;
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

std::ostream& operator<<(std::ostream& os, const Lexem& lexem) {
    std::cout << "----Token-----"
              << "\n";
    std::cout << "name: " << lexem.getWordId() << "\n";
    std::cout << "type: " << category2String(lexem.m_type) << "\n";
    std::cout << "id: " << lexem.getPosition() << "\n";
    std::cout << "--------------"
              << "\n";
    std::cout << "\n";
    return os;
}

std::string operator+(std::string& left, std::string& right) {
    std::string n = left;
    n.append(right);
    return n;
}
