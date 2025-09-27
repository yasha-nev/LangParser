
#pragma once

#include "LexemType.hpp"

struct Words {
	std::vector <std::string> operators;
	std::vector <std::string> conditions;
	std::vector <std::string> logic;
	std::vector <std::string> types;
	std::vector <std::string> keywords;
	std::vector <std::string> end;
	std::vector <std::string> programVariables;
};

class Lexem {
private:
	LexemType type;
	std::string name;
	int pos; //id in list

public:
	Lexem(int _pos, std::string str, LexemType lt) : pos(_pos), name(str), type(lt) {}
	int GetPos() { return type.Index(name); }
	int GetPos_in_Row(){ return pos; }
	std::string GetName() { return name;}
	std::string GetType() { return type.GetType(); }
	void Add_New_Key();
	void Print();
};

std::string VectorToString(std::vector <std::string> &str);
std::string operator+(std::string &left, std::string &right);