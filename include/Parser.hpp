
#pragma once

#include "EarleyItem.hpp"
#include "Grammar.hpp"
#include "Lexem.hpp"
#include "Render.hpp"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

/**
 * @class Parser
 * @brief Performs syntactic analysis using the Earley algorithm.
 */
class Parser {
public:
    /**
     * @brief Constructs the parser.
     * @param tokens Reference to a list of tokens.
     * @param grammar Reference to the grammar object.
     */
    Parser(Vocabulary& m_vocabulary, Grammar& grammar);

    void performSyntaxAnalysis(std::vector<Lexem>& m_tokens);

    void printTree();

    std::set<EarleyItem>& getParserOutput();

private:
    void scan(std::set<EarleyItem>& P_D, std::set<EarleyItem>& C_D, const Lexem& token, int pos);

    void predict(std::set<EarleyItem>& S, int pos);

    void complite(std::vector<std::set<EarleyItem>>& S, int pos);

    void throwUnexpectedToken(const Lexem& preToken, const std::set<EarleyItem>& P_D) const;

    Vocabulary& m_vocabulary;

    Grammar& m_grammar;

    std::set<EarleyItem> m_parseTree;
};
