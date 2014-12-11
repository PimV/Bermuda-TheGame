#include "ItemWood.h"
#include "Items.h"
#include <ctime>
#include <iostream>

ItemWood::ItemWood(Image* image) 
{
	this->setImage(image);
	init();
}

void ItemWood::init() {
	this->setId((int)Items::Wood);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Material);

	this->setMaxStackSize(12);

	srand(static_cast<unsigned int>(time(NULL)));
	int itemCount = rand() % 3 + 1;	
	this->setStackSize(itemCount);
}


ItemWood::~ItemWood()
{
}
