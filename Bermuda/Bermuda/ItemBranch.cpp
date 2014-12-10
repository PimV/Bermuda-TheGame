#include "ItemBranch.h"
#include "Items.h"
#include <ctime>
#include <iostream>

ItemBranch::ItemBranch(Image* image) 
{
	this->setImage(image);
	init();
}

void ItemBranch::init() {
	this->setId((int)Items::Branch);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Material);

	this->setMaxStackSize(12);

	int itemCount = 1;
	this->setStackSize(itemCount);
}


ItemBranch::~ItemBranch()
{
}
