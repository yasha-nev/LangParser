#include "Lexem_Analizator.hpp"

Lexem_Analizator::Lexem_Analizator(Words *_words) {
	words = _words;
	lexems.reserve(9);
	lexems.push_back(LexemType("KEYWORDS", "^" + VectorToString(words->keywords), &words->keywords));
	lexems.push_back(LexemType("CONDITIONS", "^" + VectorToString(words->conditions), &words->conditions));
	lexems.push_back(LexemType("LOGIC", "^" + VectorToString(words->logic), &words->logic));
	lexems.push_back(LexemType("TYPES", "^" + VectorToString(words->types), &words->types));
	lexems.push_back(LexemType("OPERATORS", "^" + VectorToString(words->operators), &words->operators));
	lexems.push_back(LexemType("VARIABLES", "^([a-zA-Z]+)", &words->programVariables));
	lexems.push_back(LexemType("END_WORDS", "^" + VectorToString(words->end), &words->end));
	lexems.push_back(LexemType("VALUE", "^(\\d+)"));
	lexems.push_back(LexemType("SPACE", "^([\\s\\n\\t]+)"));
}

void Lexem_Analizator::Analize(std::string &str, int number_of_string) {
	std::smatch m;
	std::string sup_str = str;
	while (str.size() != 0) {
		bool a = 0;
		for (size_t i = 0; i < lexems.size(); i++) {
			if (regex_search(sup_str, m, lexems[i].GetRe())) {
				if (lexems[i].GetType() != "SPACE") {
					tokens.push_back(Lexem(number_of_string, m[0].str(), lexems[i]));
					//tokens[tokens.size() - 1].Print();
				}

				std::string pref_str = m.prefix().str();
				std::string next_str = m.suffix().str();
				sup_str = pref_str + next_str;
				a = 1;
				break;
			}
		}
		if (a == 0) break;
	}
}

std::vector<Lexem> *Lexem_Analizator::GetTokens() {
	return &tokens;
}