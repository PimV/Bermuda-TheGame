#include "ItemCarrot.h"


ItemCarrot::ItemCarrot() 
{
}

void ItemCarrot::init() {
	this->setId((int)Items::Carrot);
	//this->setImage();

	this->itemTypes = std::vector<ItemType>();

	this->itemTypes.push_back(ItemType::Drink);
	this->itemTypes.push_back(ItemType::Food);

	this->setMaxStackSize(16);
}


ItemCarrot::~ItemCarrot(void)
{
}
