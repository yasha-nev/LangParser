#include "LexemType.hpp"

LexemType::LexemType(string _type, string _re) {
	re = regex(_re);
	type = _type;
	keyWords = nullptr;
}

LexemType::LexemType(string _type, string _re, vector<string> *_keyWords) {
	re = regex(_re);
	type = _type;
	keyWords = _keyWords;
}

string LexemType::GetType() { return type; }

regex LexemType::GetRe() { return re; }

int LexemType::Index(string str) {
	if (keyWords == nullptr) return -1;
	for (int i = 0; i < keyWords->size(); i++) {
		if ((*keyWords)[i] == str) return i;
	}
	//keyWords->push_back(str);
	return -1;
}

void LexemType::Add_Key_To_Array(string str)
{
	keyWords->push_back(str);
}
