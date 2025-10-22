#include "EarleyItem.hpp"

EarleyItem::EarleyItem(int vn, std::vector<int> rule, int point, int number) {
    m_vn = vn;
    m_point = point;
    m_number = number;
    m_rule.reserve(rule.size());
    m_rule.insert(m_rule.end(), rule.begin(), rule.end());
}

int EarleyItem::getVn() const noexcept {
    return m_vn;
}

int EarleyItem::getNumber() const noexcept {
    return m_number;
}

bool EarleyItem::checkEnd() const noexcept {
    return m_point == m_rule.size();
}

void EarleyItem::movePoint() noexcept {
    if(m_point < m_rule.size()) {
        m_point++;
    }
}

int EarleyItem::getQueueRule() const noexcept {
    if(checkEnd() == 1) {
        return -1;
    }
    return m_rule[m_point];
}

const std::vector<int>& EarleyItem::getRule() const noexcept {
    return m_rule;
}

bool EarleyItem::operator==(const EarleyItem& right) const noexcept {
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

bool EarleyItem::operator<(const EarleyItem& right) const noexcept {
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
