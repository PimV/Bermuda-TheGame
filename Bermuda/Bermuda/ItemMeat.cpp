#include "ItemMeat.h"
#include "Items.h"
#include <ctime>
#include <iostream>

ItemMeat::ItemMeat(Image* image) 
{
	this->setImage(image);
	init();
}

void ItemMeat::init() {
	this->setId((int)Items::Meat);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Drink);
	this->itemTypes.push_back(ItemType::Food);

	this->setMaxStackSize(16);

	srand(static_cast<unsigned int>(time(NULL)));
	int itemCount = rand() % 2 + 1;	
	this->setStackSize(itemCount);

	this->setHungerRefill(15);
	this->setThirstRefill(0);
	this->setHealthRefill(0);
}

ItemMeat::~ItemMeat()
{
}
