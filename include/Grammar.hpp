#pragma once

#include <map>

class Grammar {
public:
    void addRule(const std::string& rule, const std::vector<std::vector<std::string>>& rhs);

    const std::vector<std::vector<std::string>>& getRule(const std::string& lhs) const;

    const std::map<std::string, std::vector<std::vector<std::string>>>& getAllRules()
        const noexcept;

    int getCountElementsInRule(const std::string& rule);

private:
    std::map<std::string, std::vector<std::vector<std::string>>> m_rules;
};
