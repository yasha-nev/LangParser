
#pragma once

#include "Lexem.hpp"

class LexemAnalizator {

public:
    LexemAnalizator(Words* words);

    std::vector<Lexem>* getTokens();

    void analize(std::string& str, int numberOfRow);

private:
    std::vector<LexemType> m_lexems;

    std::vector<Lexem> m_tokens;

    Words* m_words;
};
