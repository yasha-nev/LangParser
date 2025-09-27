#include "LexemAnalizator.hpp"
#include "Parser.hpp"

#include <fstream>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Not include file" << std::endl;
        return 0;
    }

    Words w;
    w.operators = { "-", "\\+", "/", "\\*" };
    w.conditions = { "<>", "=", ">=", "<=", "<", ">" };
    w.logic = { "not", "or", "and" };
    w.types = { "%", "!", "\\$" };
    w.keywords = { "ass", "for", "while", "if",    "then",  "else",
                   "to",  "do",  "read",  "write", "begin", "end" };
    w.end = { "\\{", "\\}", ";", ":", "\\(", "\\)" };

    LexemAnalizator lexemAnalizator(&w);
    std::cout << "-----Lexems Analiz------" << "\n";

    std::fstream file(argv[1], std::ios_base::in);
    if(file.is_open()) {
        int t = 0;
        while(!file.eof()) {
            std::string str;
            std::getline(file, str);
            lexemAnalizator.analize(str, t);
            t++;
        }
    }
    file.close();

    std::vector<Lexem>* Tokens = lexemAnalizator.getTokens();
    for(int i = 0; i < Tokens->size(); i++) {
        std::cout << (*Tokens)[i] << "\n";
    }
    int k;
    std::cout << "Continute" << "\n";
    std::cin >> k;

    std::cout << "--------Parsing---------" << "\n";
    Parser p(lexemAnalizator.getTokens());
    p.parsing();
    return 0;
}
