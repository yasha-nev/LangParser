
#pragma once

#include "Lexem.hpp"

class EarleyItem {

public:
    EarleyItem(std::string vn, std::vector<std::string> rule, int point, int number);

    std::string getVn() const;

    int getNumber() const;

    std::string getQueueRule() const;

    std::vector<std::string> getRule() const;

    void movePoint();

    bool compire(const EarleyItem& Eve) const;

    bool checkEnd() const;

    bool operator<(const EarleyItem& right) const;

    friend std::ostream& operator<<(std::ostream& os, const EarleyItem& earleyItem);

private:
    std::string m_vn;

    std::vector<std::string> m_rule;

    int m_point;

    int m_number;
};
