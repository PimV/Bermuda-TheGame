#include "ItemFish.h"
#include "Items.h"
#include <ctime>
#include <iostream>


ItemFish::ItemFish()
{
	init();
}

void ItemFish::init() 
{
	this->setId((int)Items::Fish);
	this->setImage(GameStateManager::Instance()->getImageLoader()->getMapImage(GameStateManager::Instance()->getImageLoader()->loadTileset("Items\\ItemFish.png", 30,24)));

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Drink);
	this->itemTypes.push_back(ItemType::Food);

	this->setMaxStackSize(16);

	srand(time(NULL));
	int itemCount = rand() % 3 + 1;	
	this->setStackSize(itemCount);

	std::cout << "Caught " << itemCount << " fish." << std::endl;

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
