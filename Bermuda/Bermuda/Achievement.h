#pragma once
#include <string>

class Achievement
{
public:
	//methodes
	void addAmount();
	std::string getName();
	int getAmount();

	//constructor destructor
	Achievement(std::string);
	virtual ~Achievement();
private:
	std::string name;
	int amount;
};

