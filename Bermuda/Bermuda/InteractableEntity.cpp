#include "InteractableEntity.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "Camera.h"

#include <iostream>


InteractableEntity::InteractableEntity(int id, double x, double y, int chunkSize, int interactStartX, int interactStartY, int interactWidth, int interactHeight)
	: Entity(id,x,y,chunkSize)
{
	this->destroyed = false;
	this->interactStartX = interactStartX;
	this->interactStartY = interactStartY;
	this->interactWidth = interactWidth;
	this->interactHeight = interactHeight;
	this->currentInteractTime = 0;
	this->interactTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "pixelOrange.png").c_str());
}

void InteractableEntity::interact(Player* player)
{
	//TODO : oplossen op manier zonder casten
	int percentage = (int)(((double)currentInteractTime / (double)interactTime) * 100);
	cout << percentage << endl;
}

void InteractableEntity::drawInteractableArea()
{
	Camera* c = PlayState::Instance()->getCamera();

	interactRect.x = this->getX() - c->getX() + this->getInteractStartX();
	interactRect.y = this->getY() - c->getY() + this->getInteractStartY();
	interactRect.w = this->getInteractWidth();
	interactRect.h = this->getInteractHeight();
	
	GameStateManager::Instance()->sdlInitializer->drawTexture(this->interactTexture,&this->interactRect,NULL);
}

bool InteractableEntity::trackInteractTimes() {
	if (destroyed) {
		return false;
	}
	//currentInteractTime += GameStateManager::Instance()->getUpdateLength();
	currentInteractTime += GameTimer::Instance()->getFrameTime();
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
	return this->interactStartY;
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
	SDL_DestroyTexture(interactTexture);
}