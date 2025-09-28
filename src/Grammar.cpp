#include "Grammar.hpp"

void Grammar::addRule(const std::string& rule, const std::vector<std::string>& rhs) {
    auto& vec = m_rules[rule];
    vec.insert(vec.end(), rhs.begin(), rhs.end());
}

const std::vector<std::string>& Grammar::getRule(const std::string& rule) const {
    auto it = m_rules.find(rule);
    if(it != m_rules.end()) {
        return m_rules.at(rule);
    } else {
        static const std::vector<std::string> empty;
        return empty;
    }
}

const std::map<std::string, std::vector<std::string>>& Grammar::getAllRules() const noexcept {
    return m_rules;
}

int Grammar::getCountElementsInRule(const std::string& rule) {
    return m_rules.count(rule);
}
