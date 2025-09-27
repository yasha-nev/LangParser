#include "Parser.hpp"
#include <ctime>

Parser::Parser(vector<lexem>* _Tokens)
{
	Grammar["A"] = { "{ A0 } end" };
	Grammar["A0"] = { "B", "D", "B A0", "D A0"};
	Grammar["B"] = { "C : TYPES ;" , "B B"};
	Grammar["C"] = { "VARIABLES", "C , C" };
	Grammar["D"] = { "while F do { D }", "for E to G do { D }", "if F then { D }", "if F then { D } else { D }", "E", "D D"};
	Grammar["E"] = { "C ass G ;" };
	Grammar["F"] = { "F","( F )", "F or F", "F and F", "G = G", "G < G", "G <> G", "G > G", "G <= G", "G >= G", "G" };
	Grammar["G"] = { "H", "( G )", "G + G", "G - G", "G * G", "G \\ G"};
	Grammar["H"] = { "VARIABLES", "VALUE", "not F" };

	Tokens = _Tokens;
}

void Parser::Parsing()
{
	Tokens->push_back(lexem((*Tokens)[Tokens->size() - 1].GetPos_in_Row(), "", LexemType("END", "")));
	vector<set <Event>> D(Tokens->size() + 1);
	D[0].insert(Event("1A", { "A" }, 0, 0));
	try {
		for (size_t i = 0; i < Tokens->size() + 1; i++) {

			if (i > 0) {
				Scan(D[i - 1], D[i], i);
			}

			int k = -1;
			while (D[i].size() != k) {
				k = D[i].size();
				Complite(D, i);
				Predict(D[i], i);
			}

			cout << string(50, '-') << "\n";
			if (i < (*Tokens).size()) cout << i << " " << (*Tokens)[i].GetName() << "\n";
			for (const auto d : D[i]) {
				d.Print();
			}
			cout << "\n";
		}
	}
	catch (std::invalid_argument &ex) {
		cout << "----- ERROR: " << ex.what() << "-----" << "\n";
		return;
	}

	cout << "----NO ERROR FOUND PROGRAM IS TRUE----" << "\n";
	cout << "-------------Parse Tree---------------" << "\n";
	for (const auto d : ParseTree) {
		d.Print();
	}
	
}

void Parser::Scan(set <Event> &P_D, set <Event> &C_D, int pos){ //P = past, C - Current
	if (pos == 0) {
		return;
	}
	Event EndEvent("A", { "{", "A0", "}", "end"}, 4, 0);
	for (const auto d : P_D) {
		if (d.GetQueueRule() == (*Tokens)[pos - 1].GetName() ||
			d.GetQueueRule() == "TYPES" && (*Tokens)[pos - 1].GetType() == "TYPES" ||
			d.GetQueueRule() == "VALUE" && (*Tokens)[pos - 1].GetType() == "VALUE")
		{
			Event _Event = d;
			_Event.MovePoint();
			C_D.insert(_Event);
		}
		else if (d.GetQueueRule() == "VARIABLES" && (*Tokens)[pos - 1].GetType() == "VARIABLES") {
			bool a = 0;
			for (const auto d_sup : P_D) {
				if (d_sup.GetVn() == "B") {
					a = 1;
					break;
				}
			}
			if (a == 1){
				(*Tokens)[pos - 1].Add_New_Key();
			}
			else if ((*Tokens)[pos - 1].GetPos() == -1) {
				throw std::invalid_argument("Variable: " + (*Tokens)[pos - 1].GetName() + " not exist");
			}
			Event _Event = d;
			_Event.MovePoint();
			C_D.insert(_Event);
		}
		
		if (EndEvent.Compire(d) == 1 && (*Tokens)[pos - 1].GetName() != "") {
			throw  std::invalid_argument("Row " + to_string((*Tokens)[pos - 1].GetPos_in_Row()) + " symbols " + (*Tokens)[pos - 1].GetName() + " is not expected");
		}
	}
	if (C_D.size() == 0) {
		string str;
		for (const auto d : P_D) {
			if (Grammar.count(d.GetQueueRule()) == 0 && d.GetQueueRule().size() != 0){
				str = str + "," + d.GetQueueRule();
			}
		}
		if (str.size() != 0) throw std::invalid_argument("Row " + to_string((*Tokens)[pos - 1].GetPos_in_Row()) + " " + str + " is expected");
		throw std::invalid_argument("Row " + to_string((*Tokens)[pos - 1].GetPos_in_Row()) + " No symbols is expected");
	}
}

void Parser::Predict(set <Event> &D, int pos){
	set<Event> D_sup;
	for (const auto d : D) {
		if (Grammar.count(d.GetQueueRule()) == 1) {
			string sup = d.GetQueueRule();
			
			for (int i = 0; i < Grammar[sup].size(); i++) {
				Event _Event(sup, StringSplit(Grammar[sup][i]), 0, pos);
				D_sup.insert(_Event);
			}
		}
	}
	for (const auto d : D_sup) {
		D.insert(d);
	}
}

void Parser::Complite(vector <set <Event>> &D, int pos) {
	set<Event> D_Sup;
	for (const auto d : D[pos]) {
		if (d.CheckEnd() == 0){
			continue;
		}
		ParseTree.insert(d);
		int number = d.GetNumber();
		
		for (const auto s : D[number]) {
			if (s.GetQueueRule() == d.GetVn()) {
				Event _Event(s);
				_Event.MovePoint();
				D_Sup.insert(_Event);
			}
		}
	}
	for (const auto d : D_Sup) {
		D[pos].insert(d);
	}
}

vector<string> Parser::StringSplit(string str) {
	vector<string> sup;
	while (str.size() > 0) {
		int i = str.find(" ");
		if (i >= 0) {
			sup.push_back(str.substr(0, i));
			str = str.substr(i + 1);
		}
		else {
			sup.push_back(str);
			str = "";
		}
	}
	return sup;
}