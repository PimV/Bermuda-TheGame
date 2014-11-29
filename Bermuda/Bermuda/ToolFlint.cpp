#include "ToolFlint.h"
#include "Items.h"
#include <iostream>


ToolFlint::ToolFlint(Image* image) 
{
	this->setImage(image);
	init();
}

void ToolFlint::init() {
	this->setId((int)Items::Flint);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Tool);

	this->setMaxStackSize(1);

	int itemCount = 1;	
	this->setStackSize(itemCount);
}

ToolFlint::~ToolFlint()
{
}
