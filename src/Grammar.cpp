#include "Grammar.hpp"

void Grammar::addRule(int rule, const std::vector<std::vector<int>>& rhs) {
    auto& vec = m_rules[rule];
    vec.insert(vec.end(), rhs.begin(), rhs.end());
}

const std::vector<std::vector<int>>& Grammar::getRule(int rule) const {
    auto it = m_rules.find(rule);
    if(it != m_rules.end()) {
        return m_rules.at(rule);
    } else {
        static const std::vector<std::vector<int>> empty;
        return empty;
    }
}

const std::map<int, std::vector<std::vector<int>>>& Grammar::getAllRules()
    const noexcept {
    return m_rules;
}

int Grammar::getCountElementsInRule(int rule) {
    return m_rules.count(rule);
}
