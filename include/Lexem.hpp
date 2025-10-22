
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
     * @param wordId id of word in vocabulary.
     * @param position Position in the token list.
     * @param lineNumber number of the input line.
     */
    Lexem(LexemCategory type, int wordId, int position, int lineNumber);

    /** @return Token category. */
    LexemCategory getType() const noexcept;

    /** @return Token string value. */
    int getWordId() const noexcept;

    /** @return Position in the token list. */
    int getPosition() const noexcept;

    /** @return number of the input line. */
    int getLineNumber() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Lexem& lexem);

private:
    LexemCategory m_type;

    int m_wordId;

    int m_position; // id in list

    int m_lineNumber; // position in string line
};
