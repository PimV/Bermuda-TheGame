#include "ItemWood.h"
#include "Items.h"
#include <ctime>
#include <iostream>

ItemWood::ItemWood() 
{
	init();
}

void ItemWood::init() {
	this->setId((int)Items::Wood);
	this->setImage(GameStateManager::Instance()->getImageLoader()->getMapImage(GameStateManager::Instance()->getImageLoader()->loadTileset("Logs.png", 32,25)));

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Material);

	this->setMaxStackSize(12);

	srand(time(NULL));
	int itemCount = rand() % 6 + 1;	
	this->setStackSize(itemCount);

	std::cout << "Chopped " << itemCount << " logs." << std::endl;
}


ItemWood::~ItemWood(void)
{
}
