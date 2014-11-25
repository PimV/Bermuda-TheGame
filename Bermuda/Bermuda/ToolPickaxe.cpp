#include "ToolPickaxe.h"
#include "Items.h"
#include <ctime>
#include <iostream>
#include "Player.h"

ToolPickaxe::ToolPickaxe(Image* image) 
{
	this->setImage(image);
	init();
}

void ToolPickaxe::init() {
	this->setId((int)Items::Pickaxe);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Tool);

	this->setMaxStackSize(1);

	int itemCount = 1;	
	this->setStackSize(itemCount);
}

ToolPickaxe::~ToolPickaxe()
{
}
