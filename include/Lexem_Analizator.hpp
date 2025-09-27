
#pragma once

#include "Lexem.hpp"

class Lexem_Analizator {
private:
	std::vector <LexemType> lexems;
	std::vector <Lexem> tokens;
	Words *words;
public:
	Lexem_Analizator(Words *_words);
	void Analize(std::string &str, int number_of_row);
	std::vector<Lexem> *GetTokens();
};
