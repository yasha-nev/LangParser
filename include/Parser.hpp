
#pragma once

#include "Event.hpp"

class Parser
{
private:
	std::map<std::string, std::vector<std::string>> Grammar;
	std::set<Event> ParseTree;
	std::vector <Lexem> *Tokens;
	std::vector<std::string> StringSplit(std::string str);

	void Scan(std::set <Event> &P_D, std::set <Event> &C_D, int pos);
	void Predict(std::set <Event> &S, int pos);
	void Complite(std::vector <std::set <Event>> &S, int pos);

public:
	Parser(std::vector <Lexem> *_Tokens);
	void Parsing();
};