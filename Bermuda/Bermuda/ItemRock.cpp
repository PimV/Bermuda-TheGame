#include "ItemRock.h"
#include "Items.h"
#include <ctime>
#include <iostream>

ItemRock::ItemRock() 
{
	init();
}

void ItemRock::init() {
	this->setId((int)Items::Rock);
	this->setImage(GameStateManager::Instance()->getImageLoader()->getMapImage(GameStateManager::Instance()->getImageLoader()->loadTileset("Items\\ItemRock.png", 30,22)));

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Material);

	this->setMaxStackSize(8);

	srand(time(NULL));
	int itemCount = rand() % 5 + 1;	
	this->setStackSize(itemCount);

	std::cout << "Mined " << itemCount << " stone." << std::endl;
}


ItemRock::~ItemRock(void)
{
}
