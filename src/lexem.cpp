#include "lexem.hpp"

void lexem::Add_New_Key()
{
	type.Add_Key_To_Array(name);
}

void lexem::Print() {
	cout << "----Token-----" << "\n";
	cout << "name: " << name << "\n";
	cout << "type: " << GetType() << "\n";
	cout << "id: " << type.Index(name) << "\n";
	cout << "--------------" << "\n";
	cout << "\n";
}

string VectorToString(vector <string> &str) { //����������� ������ � ������ ���� (...|...|...)
	string a = "(";
	for (size_t i = 0; i < str.size(); i++) {
		a = a + str[i] + "|";
	}
	a.pop_back();
	a = a + ")";
	return a;
}

string operator+(string &left, string &right) { //���������� ��������� + ��� string
	string n = left;
	n.append(right);
	return n;
}