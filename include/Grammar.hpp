#pragma once

#include <map>
#include <string>
#include <vector>

/**
 * @class Grammar
 * @brief Stores and manages grammar rules.
 */
class Grammar {
public:
    /**
     * @brief Adds a rule to the grammar.
     * @param rule Left-hand side non-terminal.
     * @param rhs Right-hand side alternatives (list of symbol sequences).
     */
    void addRule(const std::string& rule, const std::vector<std::vector<std::string>>& rhs);

    /**
     * @brief Retrieves rules for the given non-terminal.
     * @param lhs Non-terminal (left-hand side).
     * @return List of alternative symbol sequences.
     */
    const std::vector<std::vector<std::string>>& getRule(const std::string& lhs) const;

    /**
     * @return All grammar rules.
     */
    const std::map<std::string, std::vector<std::vector<std::string>>>& getAllRules()
        const noexcept;

    /**
     * @brief Gets the number of elements in the given rule.
     * @param rule Non-terminal.
     * @return Number of elements in the rule.
     */
    int getCountElementsInRule(const std::string& rule);

private:
    std::map<std::string, std::vector<std::vector<std::string>>> m_rules;
};
