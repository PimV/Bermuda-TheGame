#include "ItemFish.h"
#include "Items.h"
#include <ctime>
#include <iostream>


ItemFish::ItemFish(Image* image)
{
	this->setImage(image);
	init();
}

void ItemFish::init() 
{
	this->setId((int)Items::Fish);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Drink);
	this->itemTypes.push_back(ItemType::Food);

	this->setMaxStackSize(16);

	srand(time(NULL));
	int itemCount = rand() % 3 + 1;	
	this->setStackSize(itemCount);

	this->setHungerRefill(5);
	this->setThirstRefill(0);
	this->setHealthRefill(0);
}

void ItemFish::consume(Player* player) {
	Consumable::consume(player);
}

ItemFish::~ItemFish()
{
}
