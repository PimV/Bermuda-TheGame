#include "Tool.h"

Tool::Tool(void)
{
	this->durability = -1;
	this->maxDurability = -1;
	this->percentageDegraded = 100;
}

void Tool::setMaxDurability(int maxDurability) {
	this->maxDurability = maxDurability;
}

int Tool::getMaxDurability() {
	return this->maxDurability;
}

void Tool::setDurability(int durability) {
	this->durability = durability;
	//casten voor percentages
	this->percentageDegraded = 100 - (static_cast<double>(this->durability) /static_cast<double>(this->maxDurability))*100;

}

int Tool::getDurability() {
	return this->durability;
}

int Tool::getPercentageDegraded() {
	return ceil(this->percentageDegraded);
}


Tool::~Tool(void)
{
}
