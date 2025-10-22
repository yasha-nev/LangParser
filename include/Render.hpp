#pragma once

#include "EarleyItem.hpp"
#include "Lexem.hpp"
#include "Vocabulary.hpp"

#include <iostream>

class Render {
public:
    Render(Vocabulary& vocabulary);

    void renderLexem(const Lexem& lexem);

    void renderEarleyItem(const EarleyItem& eItem);

protected:
    virtual std::string formatLexem(const Lexem&) const;

    virtual std::string formatEarlyItem(const EarleyItem&) const;

private:
    Vocabulary& m_vocabulary;
};
