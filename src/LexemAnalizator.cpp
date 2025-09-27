#include "LexemAnalizator.hpp"

LexemAnalizator::LexemAnalizator(Words* words) {
    m_words = words;
    m_lexems.reserve(9);
    m_lexems.push_back(
        LexemType("KEYWORDS", "^" + VectorToString(words->keywords), &words->keywords));
    m_lexems.push_back(
        LexemType("CONDITIONS", "^" + VectorToString(words->conditions), &words->conditions));
    m_lexems.push_back(LexemType("LOGIC", "^" + VectorToString(words->logic), &words->logic));
    m_lexems.push_back(LexemType("TYPES", "^" + VectorToString(words->types), &words->types));
    m_lexems.push_back(
        LexemType("OPERATORS", "^" + VectorToString(words->operators), &words->operators));
    m_lexems.push_back(LexemType("VARIABLES", "^([a-zA-Z]+)", &words->programVariables));
    m_lexems.push_back(LexemType("END_WORDS", "^" + VectorToString(words->end), &words->end));
    m_lexems.push_back(LexemType("VALUE", "^(\\d+)"));
    m_lexems.push_back(LexemType("SPACE", "^([\\s\\n\\t]+)"));
}

void LexemAnalizator::analize(std::string& str, int numberOfString) {
    std::smatch m;
    std::string sup_str = str;
    while(!str.empty()) {
        bool a = 0;
        for(size_t i = 0; i < m_lexems.size(); i++) {
            if(regex_search(sup_str, m, m_lexems[i].getRe())) {
                if(m_lexems[i].getType() != "SPACE") {
                    m_tokens.push_back(Lexem(numberOfString, m[0].str(), m_lexems[i]));
                    // tokens[tokens.size() - 1].Print();
                }

                std::string pref_str = m.prefix().str();
                std::string next_str = m.suffix().str();
                sup_str = pref_str + next_str;
                a = 1;
                break;
            }
        }
        if(a == 0) {
            break;
        }
    }
}

std::vector<Lexem>* LexemAnalizator::getTokens() {
    return &m_tokens;
}
