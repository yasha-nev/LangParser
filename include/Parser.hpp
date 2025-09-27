#pragma once
#include "Event.hpp"

class Parser
{
private:
	map<string, vector<string>> Grammar;
	set<Event> ParseTree;
	vector <lexem> *Tokens;
	vector<string> StringSplit(string str);

	void Scan(set <Event> &P_D, set <Event> &C_D, int pos);
	void Predict(set <Event> &S, int pos);
	void Complite(vector <set <Event>> &S, int pos);

public:
	Parser(vector <lexem> *_Tokens);
	void Parsing();
};