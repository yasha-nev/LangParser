#pragma once
#include "LexemType.hpp"

struct Words {
	vector <string> operators;
	vector <string> conditions;
	vector <string> logic;
	vector <string> types;
	vector <string> keywords;
	vector <string> end;
	vector <string> programVariables;
};

class lexem {
private:
	LexemType type;
	string name;
	int pos; //id in list

public:
	lexem(int _pos, string str, LexemType lt) : pos(_pos), name(str), type(lt) {}
	int GetPos() { return type.Index(name); }
	int GetPos_in_Row(){ return pos; }
	string GetName() { return name;}
	string GetType() { return type.GetType(); }
	void Add_New_Key();
	void Print();
};

string VectorToString(vector <string> &str);
string operator+(string &left, string &right);