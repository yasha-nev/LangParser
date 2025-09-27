#include "Lexem.hpp"

Lexem::Lexem(int pos, std::string name, LexemType lexemType):
    m_pos(pos),
    m_name(name),
    m_type(lexemType) {
}

int Lexem::getPos() const {
    return m_type.index(m_name);
}

int Lexem::getPosInRow() const {
    return m_pos;
}

std::string Lexem::getName() const {
    return m_name;
}

std::string Lexem::getType() const {
    return m_type.getType();
}

void Lexem::addNewKey() {
    m_type.addKeyToArray(m_name);
}

std::ostream& operator<<(std::ostream& os, const Lexem& lexem) {
    std::cout << "----Token-----" << "\n";
    std::cout << "name: " << lexem.m_name << "\n";
    std::cout << "type: " << lexem.getType() << "\n";
    std::cout << "id: " << lexem.m_type.index(lexem.m_name) << "\n";
    std::cout << "--------------" << "\n";
    std::cout << "\n";
    return os;
}

std::string VectorToString(std::vector<std::string>& str) {
    std::string a = "(";
    for(size_t i = 0; i < str.size(); i++) {
        a = a + str[i] + "|";
    }
    a.pop_back();
    a = a + ")";
    return a;
}

std::string operator+(std::string& left, std::string& right) {
    std::string n = left;
    n.append(right);
    return n;
}
