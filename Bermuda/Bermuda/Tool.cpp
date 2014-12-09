#include "Tool.h"

Tool::Tool(void)
{
	this->durability = -1;
}

void Tool::setDurability(int durability) {
	this->durability = durability;
}

int Tool::getDurability() {
	return this->durability;
}


Tool::~Tool(void)
{
}
