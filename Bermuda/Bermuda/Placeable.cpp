#include "Placeable.h"


Placeable::Placeable()
{
}

void Placeable::setPlaceEntity(Entity* entity)
{
	this->placeEntity = entity;
	entity->setEnabled(false);
}

void Placeable::Use(Player* p)
{
	this->placeEntity->setTempX(p->getX() + p->getWidth() + 10);
	this->placeEntity->setTempY(p->getY() + p->getHeight() - this->placeEntity->getHeight());
	this->placeEntity->setEnabled(true);
	
	//TODO: Somehow check collision? 

	this->placeEntity->setX(this->placeEntity->getTempX());
	this->placeEntity->setY(this->placeEntity->getTempY());
}

Placeable::~Placeable()
{
}
