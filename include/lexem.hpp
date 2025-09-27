
#pragma once

#include "LexemType.hpp"

struct Words {
    std::vector<std::string> operators;
    std::vector<std::string> conditions;
    std::vector<std::string> logic;
    std::vector<std::string> types;
    std::vector<std::string> keywords;
    std::vector<std::string> end;
    std::vector<std::string> programVariables;
};

class Lexem {
public:
    Lexem(int pos, std::string name, LexemType lexemType);

    int getPos() const;

    int getPosInRow() const;

    std::string getName() const;

    std::string getType() const;

    void addNewKey();

    friend std::ostream& operator<<(std::ostream& os, const Lexem& lexem);

private:
    LexemType m_type;

    std::string m_name;

    int m_pos; // id in list
};

std::string VectorToString(std::vector<std::string>& str);

std::string operator+(std::string& left, std::string& right);
