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

    Vocabulary vocab;
    Grammar grammar;
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

    grammar.addRule("A", { "{ A0 } end" });
    grammar.addRule("A0", { "B", "D", "B A0", "D A0" });
    grammar.addRule("B", { "C : TYPES ;", "B B" });
    grammar.addRule("B", { "C : TYPES ;", "B B" });
    grammar.addRule("C", { "VARIABLES", "C , C" });
    grammar.addRule(
        "D",
        { "while F do { D }",
          "for E to G do { D }",
          "if F then { D }",
          "if F then { D } else { D }",
          "E",
          "D D" });
    grammar.addRule("E", { "C ass G ;" });
    grammar.addRule(
        "F",
        { "F",
          "( F )",
          "F or F",
          "F and F",
          "G = G",
          "G < G",
          "G <> G",
          "G > G",
          "G <= G",
          "G >= G",
          "G" });
    grammar.addRule("G", { "H", "( G )", "G + G", "G - G", "G * G", "G \\ G" });
    grammar.addRule("H", { "VARIABLES", "VALUE", "not F" });

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

    Parser p(tokens, grammar);

    p.parsing();

    std::cout << "Continute" << "\n";
    std::cin >> k;

    p.printTree();

    return 0;
}
