#include "InteractableEntity.h"
#include "GameStateManager.h"

#include <iostream>


InteractableEntity::InteractableEntity(int id, double x, double y, int chunkSize, int rangeValue)
	: Entity(id,x,y,chunkSize)
{
	this->rangeValue = rangeValue;
	this->setRangeValues();
	this->destroyed = false;
}

void InteractableEntity::interact(Player* player)
{
	//TODO : oplossen op manier zonder casten
	cout << (int)(((double)currentInteractTime / (double)interactTime) * 100) << endl;
}

void InteractableEntity::setRangeValues()
{
	this->startX = this->getX() - this->rangeValue;
	this->endX = this->getX() + this->getWidth() + this->rangeValue;
	this->startY = this->getY() - this->rangeValue;
	this->endY = this->getY() + this->getHeight() + this->rangeValue;
}

bool InteractableEntity::trackInteractTimes() {
	if (destroyed) {
		return false;
	}
	currentInteractTime += GameStateManager::Instance()->getUpdateLength();
	if (currentInteractTime > interactTime) {
		currentInteractTime = 0;
		return true;
	}
	return false;
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