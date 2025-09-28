#include "Lexer.hpp"

Lexer::Lexer(std::vector<Lexem>& tokens, Vocabulary& vocabulary):
    m_tokens(tokens),
    m_vocabulary(vocabulary) {
}

void Lexer::tokenizeStringLine(const std::string& str, int numberOfString) {
    std::smatch m;
    std::string sup_str = str;

    while(!sup_str.empty()) {
        bool matched = false;
        for(const auto& kv: m_vocabulary.getPatterns()) {
            const LexemCategory& category = kv.first;
            const std::regex& regex = kv.second;

            if(std::regex_search(sup_str, m, regex)) {

                if(category == LexemCategory::VARIABLES) {
                    if(!m_vocabulary.contains(category, m[0])) {
                        m_vocabulary.addWord(category, m[0].str());
                    }
                }

                if(category != LexemCategory::SPACE) {
                    m_tokens.emplace_back(
                        m_vocabulary.getWordPosition(category, m[0].str()),
                        numberOfString,
                        m[0].str(),
                        category);
                }

                std::string next_str = m.suffix().str();

                if(next_str.size() == sup_str.size()) {
                    break;
                }

                sup_str = std::move(next_str);
                matched = true;
                break;
            }
        }

        if(!matched) {
            break;
        }
    }
}
