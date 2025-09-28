
#pragma once

#include "Lexem.hpp"
#include "Vocabulary.hpp"

#include <regex>

class Lexer {

public:
    Lexer(Vocabulary& vocabulary);

    void fileCodeAnalysis(const std::string& filepath);

    void tokenizeStringLine(const std::string& str, int numberOfRow);

    const std::vector<Lexem>& getTokens();

private:
    std::vector<Lexem> m_tokens;

    Vocabulary& m_vocabulary;
};
