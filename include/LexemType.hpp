#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <set>

using namespace std;

class LexemType
{
private:
	string type;
	regex re;
	vector <string> *keyWords;
public:
	LexemType(string _type, string _re);
	LexemType(string _type, string _re, vector<string> *_keyWords);
	string GetType();
	regex GetRe();
	int Index(string str);
	void Add_Key_To_Array(string str);
};