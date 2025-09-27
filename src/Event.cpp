#include "Event.hpp"

Event::Event(std::string _Vn, std::vector <std::string> _Rule, int _Point, int _Number) {
	Vn = _Vn;
	Point = _Point;
	Number = _Number;
	Rule.reserve(_Rule.size());
	for (size_t i = 0; i < _Rule.size(); i++) {
		Rule.push_back(_Rule[i]);
	}
}

bool Event::Compire(const Event &Eve) const{
	if (this->Vn == Eve.Vn &&
		this->Point == Eve.Point &&
		this->Number == Eve.Number &&
		this->Rule.size() == Eve.Rule.size())
	{
		bool flag = 1;
		for (size_t i = 0; i < Rule.size(); i++) {
			if (this->Rule[i] != Eve.Rule[i]) {
				return 0;
			}
		}
		return 1;
	}
	else return 0;
}

bool Event::CheckEnd() const{
	return Point == Rule.size();
}

void Event::MovePoint() {
	if (Point < Rule.size()) {
		Point++;
	}
}

void Event::Print() const {
	size_t n = Vn.size();
	std::cout << Vn << "-> ";
	for (int i = 0; i < Rule.size(); i++) {
		n += Rule[i].size() + 1;
		if (Point == i) {
			std::cout << "*";
		}
		std::cout << Rule[i] << " ";
	}
	if (CheckEnd()) std::cout << "*";
	std::cout << std::string(30 - n, ' ') << " | " << Point << " | " << Number << "\n";
}

std::string Event::GetQueueRule() const{
	if (CheckEnd() == 1) {
		return "";
	}
	return Rule[Point];
}

std::vector<std::string> Event::GetRule() const
{
	return Rule;
}


bool Event::operator <(const Event &right) const {
	if (this->Number != right.Number) return this->Number < right.Number;
	else if (this->Rule[0] != right.Rule[0]) return this->Rule[0]< right.Rule[0];
	else if (this->Rule.size() != right.Rule.size()) return (this->Rule.size() > right.Rule.size());
	else if (this->Vn != right.Vn) return (this->Vn < right.Vn);
	else {
		for (size_t i = 0; i < Rule.size(); i++) {
			if ((this->Rule[i] != right.Rule[i])) return (this->Rule[i] < right.Rule[i]);
		}
		return 0;
	}
}