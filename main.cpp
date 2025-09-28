#include "Lexer.hpp"
#include "Parser.hpp"
#include "Vocabulary.hpp"

#include <fstream>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Not include file" << std::endl;
        return 0;
    }

    Vocabulary vocab;
    std::vector<Lexem> tokens;
    Lexer lexer(tokens, vocab);

    vocab.addWords(LexemCategory::OPERATOR, { "-", "\\+", "/", "\\*" });
    vocab.addWords(LexemCategory::CONDITION, { "<>", "=", ">=", "<=", "<", ">" });
    vocab.addWords(LexemCategory::LOGIC, { "not", "or", "and" });
    vocab.addWords(LexemCategory::TYPES, { "%", "!", "\\$" });
    vocab.addWords(
        LexemCategory::KEYWORD,
        { "ass",
          "for",
          "while",
          "if",
          "then",
          "else",
          "to",
          "do",
          "read",
          "write",
          "begin",
          "end" });
    vocab.addWords(LexemCategory::END, { "\\{", "\\}", ";", ":", "\\(", "\\)" });
    vocab.addWords(LexemCategory::VARIABLES, { "[a-zA-Z]+" });
    vocab.addWords(LexemCategory::VALUE, { "\\d+" });
    vocab.addWords(LexemCategory::SPACE, { "[\\s\\n\\t]+" });

    std::cout << "-----Lexems Analiz------" << "\n";
    std::fstream file(argv[1], std::ios_base::in);
    if(file.is_open()) {
        int t = 0;
        while(!file.eof()) {
            std::string str;
            std::getline(file, str);
            lexer.tokenizeStringLine(str, t);
            t++;
        }
    }
    file.close();

    for(int i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i] << "\n";
    }

    int k;

    std::cout << "Continute" << "\n";
    std::cin >> k;

    std::cout << "--------Parsing---------" << "\n";

    Parser p(tokens);

    p.parsing();
    return 0;
}
