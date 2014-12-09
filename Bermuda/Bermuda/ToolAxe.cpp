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
	this->itemTypes.push_back(ItemType::WorkTool);

	this->setMaxStackSize(1);

	int itemCount = 1;	
	this->setStackSize(itemCount);

	this->setDurability(3);
	this->setMaxDurability(3);
}

ToolAxe::~ToolAxe()
{
}
