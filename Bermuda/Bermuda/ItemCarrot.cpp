#include "ItemCarrot.h"
#include "Items.h"
#include <ctime>
#include <iostream>

ItemCarrot::ItemCarrot(Image* image) 
{
	this->setImage(image);
	init();
}

void ItemCarrot::init() {
	this->setId((int)Items::Carrot);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Drink);
	this->itemTypes.push_back(ItemType::Food);

	this->setMaxStackSize(16);

	int itemCount = 1;
	this->setStackSize(itemCount);

	this->setHungerRefill(5);
	this->setThirstRefill(0);
	this->setHealthRefill(0);
}

ItemCarrot::~ItemCarrot()
{
}
