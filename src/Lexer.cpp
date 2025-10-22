#include "Lexer.hpp"

Lexer::Lexer(Vocabulary& vocabulary):
    m_vocabulary(vocabulary) {
}

void Lexer::fileCodeAnalysis(const std::string& filepath) {
    std::ifstream file(filepath);
    if(!file) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }

    std::string line;
    int lineNumber = 0;

    while(std::getline(file, line)) {
        tokenizeStringLine(line, lineNumber++);
    }
}

void Lexer::tokenizeStringLine(const std::string& str, int numberOfString) {
    std::smatch m;
    std::string sup_str = str;

    while(!sup_str.empty()) {
        bool matched = false;
        for(const auto& [category, regex]: m_vocabulary.getPatterns()) {
            if(category == LexemCategory::NOTERMINAL || category == LexemCategory::NOCATEGORY) {
                continue;
            }

            if(std::regex_search(sup_str, m, regex)) {

                if(category == LexemCategory::VARIABLES || category == LexemCategory::VALUE) {
                    if(!m_vocabulary.contains(category, m[0])) {
                        m_vocabulary.addWord(category, m[0].str());
                    }
                }

                if(category != LexemCategory::SPACE) {
                    m_tokens.emplace_back(
                        category,
                        m_vocabulary.getWordId(category, m[0].str()),
                        m_vocabulary.getWordPosition(category, m[0].str()),
                        numberOfString);
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

std::vector<Lexem>& Lexer::getTokens() {
    return m_tokens;
}
