#include "VocabularyLoader.hpp"

Vocabulary VocabularyLoader::loadFromJson(const std::string& filePath) {
    std::ifstream file(filePath);

    if(!file.is_open()) {
        throw std::runtime_error("Cannot open grammar file: " + filePath);
    }

    nlohmann::json j;
    file >> j;

    Vocabulary vocabulary;
    for(auto& it: j["vocabulary"].items()) {
        const std::string& categoryName = it.key();
        LexemCategory category;

        if(categoryName == "OPERATOR") {
            category = LexemCategory::OPERATOR;
        } else if(categoryName == "CONDITION") {
            category = LexemCategory::CONDITION;
        } else if(categoryName == "LOGIC") {
            category = LexemCategory::LOGIC;
        } else if(categoryName == "TYPES") {
            category = LexemCategory::TYPES;
        } else if(categoryName == "KEYWORD") {
            category = LexemCategory::KEYWORD;
        } else if(categoryName == "END") {
            category = LexemCategory::END;
        } else if(categoryName == "LOOP") {
            category = LexemCategory::LOOP;
        } else if(categoryName == "BRANCHING") {
            category = LexemCategory::BRANCHING;
        } else if(categoryName == "VARIABLES") {
            category = LexemCategory::VARIABLES;
        } else if(categoryName == "VALUE") {
            category = LexemCategory::VALUE;
        } else if(categoryName == "SPACE") {
            category = LexemCategory::SPACE;
        } else if(categoryName == "NONTERMINAL") {
            category = LexemCategory::NONTERMINAL;
        } else {
            throw std::runtime_error("Unknown category: " + categoryName);
        }

        for(auto& word: it.value()) {
            vocabulary.addWord(category, word.get<std::string>());
        }
    }
    file.close();

    return vocabulary;
}
