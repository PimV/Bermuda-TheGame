#include "InteractableEntity.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "Camera.h"

#include <iostream>


InteractableEntity::InteractableEntity(int id, double x, double y, int interactStartX, int interactStartY, int interactWidth, int interactHeight) : 
	Entity(id,x,y)
{
	this->destroyed = false;
	this->interactStartX = interactStartX;
	this->interactStartY = interactStartY;
	this->interactWidth = interactWidth;
	this->interactHeight = interactHeight;
	this->currentInteractTime = 0;

	this->animationType = AnimationEnumType::None;

	//TODO: pixel word voor elke interactable entity opnieuw ingeladen.
	this->interactTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "pixelOrange.png").c_str());
}

void InteractableEntity::interact(Player* player)
{

	//TODO : oplossen op manier zonder casten
	/*if (this->getEnabled())
	{
		int percentage = (int)(((double)currentInteractTime / (double)interactTime) * 100);
		cout << percentage << endl;
	}*/
}

void InteractableEntity::drawInteractableArea()
{
	if (this->getEnabled())
	{
		Camera* c = PlayState::Instance()->getCamera();

		interactRect.x = this->getX() - c->getX() + this->getInteractStartX();
		interactRect.y = this->getY() - c->getY() + this->getInteractStartY();
		interactRect.w = this->getInteractWidth();
		interactRect.h = this->getInteractHeight();

		GameStateManager::Instance()->sdlInitializer->drawTexture(this->interactTexture, &this->interactRect, NULL);
	}
}

bool InteractableEntity::trackInteractTimes() {
	if (destroyed) {
		return false;
	}

	currentInteractTime += GameTimer::Instance()->getFrameTime();
	if (currentInteractTime > interactTime) {
		currentInteractTime = 0;
		return true;
	}
	return false;
}

long InteractableEntity::getCurrentInteractTime() {
	return currentInteractTime;
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

AnimationEnumType InteractableEntity::getAnimationEnumType()
{
	return this->animationType;
}

InteractableEntity::~InteractableEntity()
{
	SDL_DestroyTexture(interactTexture);
}