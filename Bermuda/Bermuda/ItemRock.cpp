#include "ItemRock.h"
#include "Items.h"
#include <ctime>
#include <iostream>

ItemRock::ItemRock(Image* image) 
{
	this->setImage(image);
	init();
}

void ItemRock::init() {
	this->setId((int)Items::Rock);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Material);

	this->setMaxStackSize(8);

	srand(static_cast<unsigned int>(time(NULL)));
	int itemCount = rand() % 5 + 1;	
	this->setStackSize(itemCount);
}


ItemRock::~ItemRock()
{
}
