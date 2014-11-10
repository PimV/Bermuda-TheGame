#include "ToolAxe.h"
#include "Items.h"
#include <ctime>
#include <iostream>
#include "Player.h"

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

void ToolAxe::equip(Player* player) {
	Equipable::equip(player);
}

ToolAxe::~ToolAxe()
{
}
