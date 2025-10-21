
#pragma once

#include "Lexem.hpp"

#include <iostream>

/**
 * @class EarleyItem
 * @brief Represents an item of the Earley parsing algorithm.
 *
 * Holds the state of parsing: non-terminal, rule, dot position, and input index.
 */
class EarleyItem {

public:
    /**
     * @brief Constructs an Earley item.
     * @param vn Left-hand side non-terminal.
     * @param rule Grammar rule as a sequence of symbols.
     * @param point Position of the dot in the rule.
     * @param number Input index (position in the input string).
     */
    EarleyItem(int vn, std::vector<int> rule, int point, int number);

    /** @return Left-hand side non-terminal. */
    int getVn() const;

    /** @return Position in the input string. */
    int getNumber() const;

    /** @return Grammar rule as a formatted string. */
    int getQueueRule() const;

    /** @return Grammar rule as a vector of symbols. */
    std::vector<int> getRule() const;

    /** @brief Moves the dot one position forward. */
    void movePoint();

    /** @return true if the dot is at the end of the rule. */
    bool checkEnd() const;

    /** @brief Equality operator. */
    bool operator==(const EarleyItem& right) const;

    /** @brief Ordering operator (for use in sets). */
    bool operator<(const EarleyItem& right) const;

    friend std::ostream& operator<<(std::ostream& os, const EarleyItem& earleyItem);

private:
    int m_vn;

    std::vector<int> m_rule;

    int m_point;

    int m_number;
};
