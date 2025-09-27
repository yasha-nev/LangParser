#include "Lexem.hpp"

void Lexem::Add_New_Key()
{
	type.Add_Key_To_Array(name);
}

void Lexem::Print() {
	std::cout << "----Token-----" << "\n";
	std::cout << "name: " << name << "\n";
	std::cout << "type: " << GetType() << "\n";
	std::cout << "id: " << type.Index(name) << "\n";
	std::cout << "--------------" << "\n";
	std::cout << "\n";
}

std::string VectorToString(std::vector <std::string> &str) {
	std::string a = "(";
	for (size_t i = 0; i < str.size(); i++) {
		a = a + str[i] + "|";
	}
	a.pop_back();
	a = a + ")";
	return a;
}

std::string operator+(std::string &left, std::string &right) {
	std::string n = left;
	n.append(right);
	return n;
}