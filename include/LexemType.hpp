
#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <set>

class LexemType
{
private:
	std::string type;
	std::regex re;
	std::vector <std::string> *keyWords;
public:
	LexemType(std::string _type, std::string _re);
	LexemType(std::string _type, std::string _re, std::vector<std::string> *_keyWords);
	std::string GetType();
	std::regex GetRe();
	int Index(std::string str);
	void Add_Key_To_Array(std::string str);
};