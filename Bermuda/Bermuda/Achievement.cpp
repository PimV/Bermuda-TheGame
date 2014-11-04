#include "Achievement.h"


Achievement::Achievement(std::string str)
{
	name = str;
	amount = 0;
}

int Achievement::getAmount()
{
	return amount;
}

std::string Achievement::getName()
{
	return name;
}

void Achievement::addAmount()
{
	amount++;
}

Achievement::~Achievement()
{
}
