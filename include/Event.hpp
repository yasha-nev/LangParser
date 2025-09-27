
#pragma once

#include "Lexem.hpp"

class Event{
private:
	std::string Vn;
	std::vector <std::string> Rule;
	int Point;
	int Number;
public:
	Event(std::string _Vn, std::vector <std::string> _Rule, int _Point, int _Number);
	void MovePoint();
	void Print() const;
	
	std::string GetVn() const { return Vn; }
	int GetNumber() const { return Number; }
	std::string GetQueueRule() const;
	std::vector <std::string> GetRule() const;

	bool operator <(const Event &right) const;
	bool Compire(const Event &Eve) const;
	bool CheckEnd() const;
};

