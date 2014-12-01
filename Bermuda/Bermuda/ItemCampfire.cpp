#include "ItemCampfire.h"
#include "Campfire.h"
#include "ObjectFactory.h"
#include "Objects.h"


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
}

void ItemCampfire::use(Player* p)
{
	int x = p->getX() + p->getWidth() + 10;
	int y = p->getY() + p->getHeight() - 52;

	//TODO: object factory
	Campfire* campfire = dynamic_cast<Campfire*>(ObjectFactory::Instance()->createObject(Objects::Campfire, 0, x, y));

	//if collision, delete Campfire and keep item.
	if (campfire->checkCollision())
	{
		delete campfire;
	}
	else
	{
		p->getInventory()->deleteItemFromStack(this, 1);
	}
}

ItemCampfire::~ItemCampfire()
{
}
