#pragma once

/**
 * @enum LexemCategory
 * @brief Defines categories of lexical tokens.
 */
enum class LexemCategory {
    OPERATOR,
    CONDITION,
    LOGIC,
    TYPES,
    LOOP,
    BRANCHING,
    KEYWORD,
    END,
    END_WORDS,
    VALUE,
    SPACE,
    VARIABLES,
    NONTERMINAL,
    NOCATEGORY
};
