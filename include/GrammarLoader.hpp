#pragma once

#include "Grammar.hpp"
#include "nlohmann/json.hpp"

#include <fstream>

class GrammarLoader {
public:
    static Grammar loadFromJson(const std::string& filePath);
};
