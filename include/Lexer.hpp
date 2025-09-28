
#pragma once

#include "Lexem.hpp"
#include "Vocabulary.hpp"

#include <regex>

class Lexer {

public:
    Lexer(std::vector<Lexem>& m_tokens, Vocabulary& vocabulary);

    void tokenizeStringLine(const std::string& str, int numberOfRow);

private:
    std::vector<Lexem>& m_tokens;

    Vocabulary& m_vocabulary;
};
