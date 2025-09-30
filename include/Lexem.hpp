
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
     * @param position Position in the token list.
     * @param positionInRow Position in the input line.
     * @param name Token string value.
     * @param type Token category.
     */
    Lexem(int position, int positionInRow, std::string name, LexemCategory type);

    /** @return Position in the token list. */
    int getPosition() const;

    /** @return Position in the input line. */
    int getPositionInRow() const;

    /** @return Token string value. */
    std::string getName() const;

    /** @return Token category. */
    LexemCategory getType() const;

    friend std::ostream& operator<<(std::ostream& os, const Lexem& lexem);

private:
    LexemCategory m_type;

    std::string m_name;

    int m_position; // id in list

    int m_positionInRow; // position in string line
};

std::string operator+(std::string& left, std::string& right);
