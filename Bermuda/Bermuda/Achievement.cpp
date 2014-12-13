#include "Achievement.h"


Achievement::Achievement(std::string str)
{
	name = str;
	this->amount = 0;
}

int Achievement::getAmount()
{
	return this->amount;
}

std::string Achievement::getName()
{
	return this->name;
}

void Achievement::addAmount()
{
	this->amount++;
}

void Achievement::setAmount(int amount)
{
	this->amount = amount;
}

Achievement::~Achievement()
{
}
