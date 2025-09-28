#include "GrammarLoader.hpp"

Grammar GrammarLoader::loadFromJson(const std::string& filePath) {
    std::ifstream file(filePath);

    if(!file.is_open()) {
        throw std::runtime_error("Cannot open grammar file: " + filePath);
    }

    nlohmann::json j;
    file >> j;
    Grammar grammar;
    for(auto& it: j["rules"].items()) {
        const std::string& lhs = it.key();
        std::vector<std::vector<std::string>> rule;
        for(auto& alt: it.value()) {
            std::vector<std::string> rhs;
            for(auto& symbol: alt) {
                rhs.push_back(symbol.get<std::string>());
            }
            rule.push_back(rhs);
        }
        grammar.addRule(lhs, rule);
    }
    file.close();

    return grammar;
}
