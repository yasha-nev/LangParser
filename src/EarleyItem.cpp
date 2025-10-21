#include "EarleyItem.hpp"

EarleyItem::EarleyItem(int vn, std::vector<int> rule, int point, int number) {
    m_vn = vn;
    m_point = point;
    m_number = number;
    m_rule.reserve(rule.size());
    for(size_t i = 0; i < rule.size(); i++) {
        m_rule.push_back(rule[i]);
    }
}

int EarleyItem::getVn() const {
    return m_vn;
}

int EarleyItem::getNumber() const {
    return m_number;
}

bool EarleyItem::checkEnd() const {
    return m_point == m_rule.size();
}

void EarleyItem::movePoint() {
    if(m_point < m_rule.size()) {
        m_point++;
    }
}

std::ostream& operator<<(std::ostream& os, const EarleyItem& eItem) {
    os << eItem.m_vn << " -> ";

    for(int i = 0; i < eItem.m_rule.size(); i++) {
        if(eItem.m_point == i) {
            std::cout << "*";
        }
        std::cout << eItem.m_rule[i] << " ";
    }
    if(eItem.checkEnd()) {
        std::cout << "*";
    }
    os << std::string(30, ' ') << " | " << eItem.m_point << " | " << eItem.m_number << "\n";

    return os;
}

int EarleyItem::getQueueRule() const {
    if(checkEnd() == 1) {
        return -1;
    }
    return m_rule[m_point];
}

std::vector<int> EarleyItem::getRule() const {
    return m_rule;
}

bool EarleyItem::operator==(const EarleyItem& right) const {
    if(this->m_vn == right.m_vn && this->m_point == right.m_point &&
       this->m_number == right.m_number && this->m_rule.size() == right.m_rule.size()) {

        bool flag = 1;
        for(size_t i = 0; i < m_rule.size(); i++) {
            if(this->m_rule[i] != right.m_rule[i]) {
                return 0;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

bool EarleyItem::operator<(const EarleyItem& right) const {
    if(this->m_number != right.m_number) {
        return this->m_number < right.m_number;
    } else if(this->m_vn != right.m_vn) {
        return (this->m_vn < right.m_vn);
    } else if(this->m_rule[0] != right.m_rule[0]) {
        return this->m_rule[0] < right.m_rule[0];
    } else if(this->m_rule.size() != right.m_rule.size()) {
        return (this->m_rule.size() > right.m_rule.size());
    } else {
        for(size_t i = 0; i < m_rule.size(); i++) {
            if((this->m_rule[i] != right.m_rule[i])) {
                return (this->m_rule[i] < right.m_rule[i]);
            }
        }
        return 0;
    }
}
