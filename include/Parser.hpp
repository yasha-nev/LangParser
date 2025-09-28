
#pragma once

#include "EarleyItem.hpp"
#include "Grammar.hpp"
#include "Lexem.hpp"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Parser {

public:
    Parser(std::vector<Lexem>& tokens, Grammar& grammar);

    void parsing();

    void printTree();

private:
    void scan(std::set<EarleyItem>& P_D, std::set<EarleyItem>& C_D, int pos);

    void predict(std::set<EarleyItem>& S, int pos);

    void complite(std::vector<std::set<EarleyItem>>& S, int pos);

    void throwUnexpectedToken(const Lexem& preToken, const std::set<EarleyItem>& P_D) const;

    void printLineScan(int line, const Lexem& token, std::set<EarleyItem>& D);

    Grammar& m_grammar;

    std::set<EarleyItem> m_parseTree;

    std::vector<Lexem>& m_tokens;
};
