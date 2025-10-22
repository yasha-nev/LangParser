#include "GrammarLoader.hpp"

Grammar GrammarLoader::loadFromJson(const std::string& filePath, const Vocabulary &vocabulary) {
    std::ifstream file(filePath);

    if(!file.is_open()) {
        throw std::runtime_error("Cannot open grammar file: " + filePath);
    }

    nlohmann::json j;
    file >> j;
    Grammar grammar;
    for(auto& it: j["rules"].items()) {
        const std::string& lhs = it.key();
        std::vector<std::vector<int>> rule;
        for(auto& alt: it.value()) {
            std::vector<int> rhs;
            for(auto& symbol: alt) {
                std::string s = symbol.get<std::string>();
                rhs.push_back( vocabulary.getWordId(s) );
            }
            rule.push_back( rhs);
        }
        grammar.addRule(vocabulary.getWordId(lhs), rule);
    }
    file.close();

    return grammar;
}
