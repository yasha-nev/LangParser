
#pragma once

#include "Vocabulary.hpp"

#include <LexemCategory.hpp>
#include <iostream>

class Lexem {
public:
    Lexem(int position, int positionInRow, std::string name, LexemCategory type);

    int getPosition() const;

    int getPositionInRow() const;

    std::string getName() const;

    LexemCategory getType() const;

    friend std::ostream& operator<<(std::ostream& os, const Lexem& lexem);

private:
    LexemCategory m_type;

    std::string m_name;

    int m_position; // id in list

    int m_positionInRow; // position in string line
};

std::string operator+(std::string& left, std::string& right);
