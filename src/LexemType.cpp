#include "LexemType.hpp"

LexemType::LexemType(std::string _type, std::string _re) {
	re = std::regex(_re);
	type = _type;
	keyWords = nullptr;
}

LexemType::LexemType(std::string _type, std::string _re, std::vector<std::string> *_keyWords) {
	re = std::regex(_re);
	type = _type;
	keyWords = _keyWords;
}

std::string LexemType::GetType() { return type; }

std::regex LexemType::GetRe() { return re; }

int LexemType::Index(std::string str) {
	if (keyWords == nullptr) return -1;
	for (int i = 0; i < keyWords->size(); i++) {
		if ((*keyWords)[i] == str) return i;
	}
	//keyWords->push_back(str);
	return -1;
}

void LexemType::Add_Key_To_Array(std::string str)
{
	keyWords->push_back(str);
}
