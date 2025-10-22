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
    KEYWORD,
    END,
    END_WORDS,
    VALUE,
    SPACE,
    VARIABLES,
    NOTERMINAL,
    NOCATEGORY
};
