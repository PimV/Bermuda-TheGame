#include "ItemWood.h"
#include "Items.h"
#include <ctime>
#include <iostream>

ItemWood::ItemWood(Image* image) 
{
	init(image);
}

void ItemWood::init(Image* image) {
	this->setId((int)Items::Wood);
	this->setImage(GameStateManager::Instance()->getImageLoader()->getMapImage(GameStateManager::Instance()->getImageLoader()->loadTileset("Items\\ItemLogs.png", 32,25)));

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Material);

	this->setMaxStackSize(12);

	srand(time(NULL));
	int itemCount = rand() % 3 + 1;	
	this->setStackSize(itemCount);

	std::cout << "Chopped " << itemCount << " logs." << std::endl;
}


ItemWood::~ItemWood()
{
}
