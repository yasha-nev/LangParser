
#pragma once

#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

class LexemType {
public:
    LexemType(std::string type, std::string re);

    LexemType(std::string type, std::string re, std::vector<std::string>* keyWords);

    std::string getType() const;

    std::regex getRe();

    int index(std::string str) const;

    void addKeyToArray(std::string str);

private:
    std::string m_type;

    std::regex m_re;

    std::vector<std::string>* m_keyWords;
};
