#include "ItemCampfire.h"
#include "Campfire.h"
#include "ObjectFactory.h"
#include "Objects.h"
#include "MovementDirectionEnum.h"


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
	if (!p->getInventory()->hasItemById((int)Items::Flint)) {
		return;
	}
	double x = 0;
	double y = 0;

	switch (p->getMovementDirection())
	{
	case MovementDirectionEnum::Left:
		x = p->getX() + p->getCollisionX() - 15 - 50;
		y = p->getY() + p->getHeight() - 52;
		break;
	case MovementDirectionEnum::Up:
		x = p->getX() + p->getWidth() / 2 - 25;
		y = p->getY() + p->getCollisionY() - 15 - 52;
		break;
	case MovementDirectionEnum::Right:
		x = p->getX() + p->getCollisionX() + p->getCollisionWidth() + 15;
		y = p->getY() + p->getHeight() - 52;
		break;
	case MovementDirectionEnum::Down:
		x = p->getX() + p->getWidth() / 2 - 25;
		y = p->getY() + p->getHeight() + 15 - 31;
		break;
	default:
		return;
		break;
	}

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
