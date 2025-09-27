#include "LexemType.hpp"

LexemType::LexemType(std::string _type, std::string _re) {
    m_re = std::regex(_re);
    m_type = _type;
    m_keyWords = nullptr;
}

LexemType::LexemType(std::string _type, std::string _re, std::vector<std::string>* _keyWords) {
    m_re = std::regex(_re);
    m_type = _type;
    m_keyWords = _keyWords;
}

std::string LexemType::getType() const {
    return m_type;
}

std::regex LexemType::getRe() {
    return m_re;
}

int LexemType::index(std::string str) const {
    if(m_keyWords == nullptr) {
        return -1;
    }
    for(int i = 0; i < m_keyWords->size(); i++) {
        if((*m_keyWords)[i] == str) {
            return i;
        }
    }
    // keyWords->push_back(str);
    return -1;
}

void LexemType::addKeyToArray(std::string str) {
    m_keyWords->push_back(str);
}
