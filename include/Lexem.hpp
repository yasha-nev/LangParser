
#pragma once

#include "Vocabulary.hpp"

#include <LexemCategory.hpp>
#include <iostream>

/**
 * @class Lexem
 * @brief Represents a lexical token.
 */
class Lexem {
public:
    /**
     * @brief Constructs a lexical token.
     * @param type Token category.
     * @param wordId Token word id in vocabulary.
     * @param position Position in the token list.
     * @param lineNumber Position in the input line.
     */
    Lexem(LexemCategory type, int wordId, int position, int lineNumber);

    /** @return Token category. */
    LexemCategory getType() const;

    /** @return Token string value. */
    int getWordId() const;

    /** @return Position in the token list. */
    int getPosition() const;

    /** @return Position in the input line. */
    int getLineNumber() const;

    friend std::ostream& operator<<(std::ostream& os, const Lexem& lexem);

private:
    LexemCategory m_type;

    int m_wordId;

    int m_position;

    int m_lineNumber;
};

std::string operator+(std::string& left, std::string& right);
