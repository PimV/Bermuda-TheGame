#include "Achievement.h"


Achievement::Achievement(std::string str)
{
	name = str;
	amount = 0;
}

void Achievement::addAmount()
{
	amount++;
}

Achievement::~Achievement()
{
}
