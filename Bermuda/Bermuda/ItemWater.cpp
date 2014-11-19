#include "ItemWater.h"
#include "Items.h"
#include <iostream>

ItemWater::ItemWater(Image* image) 
{
	this->setImage(image);
	init();
}

void ItemWater::init() {
	this->setId((int)Items::Water);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Drink);

	this->setMaxStackSize(6);

	int itemCount = 1;
	this->setStackSize(itemCount);

	std::cout << "Gained " << itemCount << " water." << std::endl;

	this->setHungerRefill(0);
	this->setThirstRefill(10);
	this->setHealthRefill(0);
}

void ItemWater::consume(Player* player) {
	Consumable::consume(player);
}



ItemWater::~ItemWater()
{
}
