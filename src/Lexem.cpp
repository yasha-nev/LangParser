#include "Lexem.hpp"

Lexem::Lexem(int position, int positionInRow, std::string name, LexemCategory type):
    m_type(type),
    m_name(name),
    m_position(position),
    m_positionInRow(positionInRow) {
}

int Lexem::getPosition() const {
    return m_position;
}

int Lexem::getPositionInRow() const {
    return m_positionInRow;
}

std::string Lexem::getName() const {
    return m_name;
}

LexemCategory Lexem::getType() const {
    return m_type;
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
    std::cout << "name: " << lexem.m_name << "\n";
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
