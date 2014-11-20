#include "ItemGold.h"
#include "Items.h"
#include <iostream>

ItemGold::ItemGold(Image* image) 
{
	this->setImage(image);
	init();
}

void ItemGold::init() {
	this->setId((int)Items::Gold);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Material);

	this->setMaxStackSize(12);

	int itemCount = 1;
	this->setStackSize(itemCount);

	std::cout << "Mined " << itemCount << " gold." << std::endl;
}

ItemGold::~ItemGold()
{
}
