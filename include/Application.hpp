#pragma once

#include "Grammar.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Vocabulary.hpp"
#include "ast/Ast.hpp"

#include <string>

/**
 * @class Application
 * @brief Main application class for running syntax analysis.
 */
class Application {
public:
    /**
     * @brief Constructs the application.
     * @param grammarFile Path to the grammar file.
     * @param vocabFile Path to the vocabulary file.
     */
    Application(const std::string& grammarFile, const std::string& vocabFile);

    /**
     * @brief Runs the analysis on the given source file.
     * @param sourceFile Path to the source file.
     */
    void run(const std::string& sourceFile);

private:
    Vocabulary m_vocabulary;

    Grammar m_grammar;

    Lexer m_lexer;

    Parser m_parser;
};
