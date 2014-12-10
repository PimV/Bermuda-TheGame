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

	this->highlightTexture = nullptr;

	this->animationType = AnimationEnumType::None;

	//TODO: pixel word voor elke interactable entity opnieuw ingeladen.
	this->interactTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "pixelOrange.png").c_str());
}

void InteractableEntity::interact(Player* player)
{
	//TODO : oplossen op manier zonder casten
	if (this->getEnabled())
	{
	int percentage = (int)(((double)currentInteractTime / (double)interactTime) * 100);
	cout << percentage << endl;
	}
}

void InteractableEntity::setCanInteractTexture(SDL_Texture* can)
{
	this->canInteractTexture = can;
}

void InteractableEntity::setCantInteractTexture(SDL_Texture* cant)
{
	this->cantInteractTexture = cant;
}

SDL_Texture* InteractableEntity::getCanInteractTexture()
{
	return this->canInteractTexture;
}
SDL_Texture* InteractableEntity::getCantInteractTexture()
{
	return this->cantInteractTexture;
}

bool InteractableEntity::canInteract(Player* player) {
	return true;
}

void InteractableEntity::setHighlightTexture(SDL_Texture* texture) {
	this->highlightTexture = texture;
}

void InteractableEntity::setHighlightImage(Image* img) {
	this->highlightImage = img;
}

Image* InteractableEntity::getHighlightImage() {
	return this->highlightImage;
}

SDL_Texture* InteractableEntity::getHighlightTexture() {
	return this->highlightTexture;
}

void InteractableEntity::highlight() {
	if (this->highlightTexture != nullptr) {
		Camera* c = PlayState::Instance()->getCamera();
		SDL_Rect rect;
		rect.x = this->getX() - c->getX();
		rect.y = this->getY() - c->getY();
		rect.w = this->getWidth();
		rect.h = this->getHeight();
		//SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), highlightImage->getTileSet(), highlightImage->getCroppingRect(), &rect);
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), this->highlightTexture, NULL, &rect);
	}
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