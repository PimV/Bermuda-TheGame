#include "ItemCampfire.h"


ItemCampfire::ItemCampfire(Image* image)
{
	this->setImage(image);
	init();
}

void ItemCampfire::init()
{
	this->setId((int)Items::Campfire);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Buildable);
	this->setMaxStackSize(1);
	this->setStackSize(1);

	//Todo: set the entity to place when using this item. (new campfire entity)
	//this->setPlaceEntity();
}

ItemCampfire::~ItemCampfire()
{
}
