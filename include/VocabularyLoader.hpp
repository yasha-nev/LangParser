#pragma once

#include "Vocabulary.hpp"
#include "nlohmann/json.hpp"

#include <fstream>

class VocabularyLoader {
public:
    static Vocabulary loadFromJson(const std::string& filePath);
};
