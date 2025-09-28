#include "Grammar.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Vocabulary.hpp"

#include <fstream>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Not include file" << std::endl;
        return 0;
    }

    Vocabulary vocabulary;
    Grammar grammar;
    Lexer lexer(vocabulary);

    vocabulary.loadFromJson("configuration.json");
    grammar.loadFromJson("configuration.json");

    lexer.fileCodeAnalysis(argv[1]);
    auto tokens = lexer.getTokens();

    for(int i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i] << "\n";
    }

    int k;

    std::cout << "Continute" << "\n";
    std::cin >> k;

    Parser p(tokens, grammar);

    p.parsing();

    std::cout << "Continute" << "\n";
    std::cin >> k;

    p.printTree();

    return 0;
}
