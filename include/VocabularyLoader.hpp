#pragma once

#include "Vocabulary.hpp"
#include "nlohmann/json.hpp"

#include <fstream>

/**
 * @class VocabularyLoader
 * @brief Loads vocabulary from a JSON file.
 */
class VocabularyLoader {
public:
    /**
     * @brief Loads vocabulary from a JSON file.
     * @param filePath Path to the JSON file.
     * @return Vocabulary object.
     */
    static Vocabulary loadFromJson(const std::string& filePath);
};
