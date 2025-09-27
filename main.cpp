#include <fstream>
#include "Lexem_Analizator.hpp"
#include "Parser.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		cout << "Not include file" << endl;
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
	cout << "-----Lexems Analiz------" << "\n";

	fstream file(argv[1], ios_base::in);
	if (file.is_open()) {
		int t = 0;
		while (!file.eof()) {
			string str;
			getline(file, str);
			la.Analize(str, t);
			t++;
		}
	}
	file.close();

	vector <lexem> *Tokens = la.GetTokens();
	for (int i = 0; i < Tokens->size(); i++) {
		(*Tokens)[i].Print();
	}
	int k;
	cout << "Continute" << "\n";
	cin >> k;

	cout << "--------Parsing---------" << "\n";
	Parser p(la.GetTokens());
	p.Parsing();
	return 0;
}