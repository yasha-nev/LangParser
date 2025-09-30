#pragma once

#include "Grammar.hpp"
#include "nlohmann/json.hpp"

#include <fstream>

/**
 * @class GrammarLoader
 * @brief Loads grammar rules from a JSON file.
 */
class GrammarLoader {
public:
    /**
     * @brief Loads grammar from a JSON file.
     * @param filePath Path to the JSON file.
     * @return Grammar object.
     */
    static Grammar loadFromJson(const std::string& filePath);
};
