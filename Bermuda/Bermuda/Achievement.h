#pragma once
#include <string>

class Achievement
{
private:
	std::string name;
	int amount;
public:
	Achievement(std::string);
	//methodes
	void addAmount();
	std::string getName();
	int getAmount();
	void setAmount(int amount);

	virtual ~Achievement();
};

