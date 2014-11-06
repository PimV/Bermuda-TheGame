#include "ItemCarrot.h"
#include "Items.h"
#include <ctime>
#include <iostream>

ItemCarrot::ItemCarrot() 
{
	init();
}

void ItemCarrot::init() {
	this->setId((int)Items::Carrot);
	this->setImage(GameStateManager::Instance()->getImageLoader()->getMapImage(GameStateManager::Instance()->getImageLoader()->loadTileset("Items\\ItemCarrot.png", 30,22)));

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Drink);
	this->itemTypes.push_back(ItemType::Food);

	this->setMaxStackSize(16);

	srand(time(NULL));
	int itemCount = rand() % 2 + 1;	
	this->setStackSize(itemCount);

	std::cout << "Harvested " << itemCount << " carrots." << std::endl;

	this->setHungerRefill(5);
	this->setThirstRefill(0);
	this->setHealthRefill(0);
}

void ItemCarrot::consume(Player* player) {
	Consumable::consume(player);
}


ItemCarrot::~ItemCarrot(void)
{
}
