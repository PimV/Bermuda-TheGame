#include "InteractableEntity.h"
#include "GameStateManager.h"

#include <iostream>


InteractableEntity::InteractableEntity(int id, double x, double y, int chunkSize, int interactStartX, int interactStartY, int interactWidth, int interactHeight)
	: Entity(id,x,y,chunkSize)
{
	this->destroyed = false;
	this->interactStartX = interactStartX;
	this->interactStartY = interactStartY;
	this->interactWidth = interactWidth;
	this->interactHeight = interactHeight;

}

void InteractableEntity::interact(Player* player)
{
	//TODO : oplossen op manier zonder casten
	cout << (int)(((double)currentInteractTime / (double)interactTime) * 100) << endl;
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

int InteractableEntity::getInteractStartX()
{
	return this->interactStartX;
}

int InteractableEntity::getInteractStartY()
{
	return this->interactStartX;
}

int InteractableEntity::getInteractWidth()
{
	return this->interactWidth;
}

int InteractableEntity::getInteractHeight()
{
	return this->interactHeight;
}

void InteractableEntity::setDestroyedState() {}

InteractableEntity::~InteractableEntity()
{
}