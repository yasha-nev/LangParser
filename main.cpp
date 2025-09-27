#include <fstream>
#include "Lexem_Analizator.hpp"
#include "Parser.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		std::cout << "Not include file" << std::endl;
		return 0;
	}

	Words w;
	w.operators = { "-", "\\+", "/", "\\*" };
	w.conditions = { "<>", "=", ">=", "<=", "<", ">"};
	w.logic = { "not", "or", "and"};
	w.types = { "%", "!", "\\$"};
	w.keywords = { "ass", "for", "while", "if", "then", "else", "to", "do", "read", "write", "begin", "end"};
	w.end = { "\\{", "\\}", ";", ":", "\\(", "\\)"};

	Lexem_Analizator la(&w);
	std::cout << "-----Lexems Analiz------" << "\n";

	std::fstream file(argv[1], std::ios_base::in);
	if (file.is_open()) {
		int t = 0;
		while (!file.eof()) {
			std::string str;
			std::getline(file, str);
			la.Analize(str, t);
			t++;
		}
	}
	file.close();

	std::vector <Lexem> *Tokens = la.GetTokens();
	for (int i = 0; i < Tokens->size(); i++) {
		(*Tokens)[i].Print();
	}
	int k;
	std::cout << "Continute" << "\n";
	std::cin >> k;

	std::cout << "--------Parsing---------" << "\n";
	Parser p(la.GetTokens());
	p.Parsing();
	return 0;
}