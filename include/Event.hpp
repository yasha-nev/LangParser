#pragma once
#include "lexem.hpp"

class Event{
private:
	string Vn;
	vector <string> Rule;
	int Point;
	int Number;
public:
	Event(string _Vn, vector <string> _Rule, int _Point, int _Number);
	void MovePoint();
	void Print() const;
	
	string GetVn() const { return Vn; }
	int GetNumber() const { return Number; }
	string GetQueueRule() const;
	vector <string> GetRule() const;

	bool operator <(const Event &right) const;
	bool Compire(const Event &Eve) const;
	bool CheckEnd() const;
};

