#include "ItemApple.h"
#include "Items.h"
#include <ctime>
#include <iostream>

ItemApple::ItemApple(Image* image) 
{
	this->setImage(image);
	init();
}

void ItemApple::init() {
	this->setId((int)Items::Apple);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Drink);
	this->itemTypes.push_back(ItemType::Food);

	this->setMaxStackSize(16);

	srand(time(NULL));
	int itemCount = rand() % 2 + 1;	
	this->setStackSize(itemCount);

	this->setHungerRefill(5);
	this->setThirstRefill(5);
	this->setHealthRefill(0);
}

void ItemApple::consume(Player* player) {
	Consumable::consume(player);
}


ItemApple::~ItemApple()
{
}
