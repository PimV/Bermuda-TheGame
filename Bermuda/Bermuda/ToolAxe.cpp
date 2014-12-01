#include "ToolAxe.h"
#include "Items.h"
#include "Player.h"
#include <iostream>

ToolAxe::ToolAxe(Image* image) 
{
	this->setImage(image);
	init();
}

void ToolAxe::init() {
	this->setId((int)Items::Axe);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Tool);

	this->setMaxStackSize(1);

	int itemCount = 1;	
	this->setStackSize(itemCount);
}

ToolAxe::~ToolAxe()
{
}
