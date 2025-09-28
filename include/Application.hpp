#pragma once

#include "Grammar.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Vocabulary.hpp"

#include <string>

class Application {
public:
    Application(const std::string& grammarFile, const std::string& vocabFile);

    void run(const std::string& sourceFile);

private:
    Vocabulary m_vocabulary;

    Grammar m_grammar;

    Lexer m_lexer;

    Parser m_parser;
};
