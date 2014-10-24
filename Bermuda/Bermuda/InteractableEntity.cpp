#include "InteractableEntity.h"


InteractableEntity::InteractableEntity(int id, double x, double y, int chunkSize, int rangeValue)
	: Entity(id,x,y,chunkSize)
{
	this->rangeValue = rangeValue;
	this->setRangeValues();
}

void InteractableEntity::setRangeValues()
{
	this->startX = this->getX() - this->rangeValue;
	this->endX = this->getX() + this->getWidth() + this->rangeValue;
	this->startY = this->getY() - this->rangeValue;
	this->endY = this->getY() + this->getHeight() + this->rangeValue;
}

int InteractableEntity::getRangeValue()
{
	return this->rangeValue;
}

int InteractableEntity::getInteractAreaStartX()
{
	return this->startX;
}

int InteractableEntity::getInteractAreaEndX()
{
	return this->endX;
}

int InteractableEntity::getInteractAreaStartY()
{
	return this->startY;
}

int InteractableEntity::getInteractAreaEndY()
{
	return this->endY;
}

InteractableEntity::~InteractableEntity()
{
}