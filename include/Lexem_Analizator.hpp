#pragma once
#include "lexem.hpp"

class Lexem_Analizator {
private:
	vector <LexemType> lexems;
	vector <lexem> tokens;
	Words *words;
public:
	Lexem_Analizator(Words *_words);
	void Analize(string &str, int number_of_row);
	vector<lexem> *GetTokens();
};
