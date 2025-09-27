
#pragma once

#include "EarleyItem.hpp"

class Parser {

public:
    Parser(std::vector<Lexem>* _Tokens);

    void parsing();

private:
    void scan(std::set<EarleyItem>& P_D, std::set<EarleyItem>& C_D, int pos);

    void predict(std::set<EarleyItem>& S, int pos);

    void complite(std::vector<std::set<EarleyItem>>& S, int pos);

    std::vector<std::string> stringSplit(std::string str);

    std::map<std::string, std::vector<std::string>> m_grammar;

    std::set<EarleyItem> m_parseTree;

    std::vector<Lexem>* m_tokens;
};
