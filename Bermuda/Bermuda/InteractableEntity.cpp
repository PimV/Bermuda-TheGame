#include "InteractableEntity.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "Camera.h"
#include "Equipable.h"

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
	this->percentageCompleted = 0;

	this->highlightTexture = nullptr;

	this->animationType = AnimationEnumType::None;

	//TODO: pixel word voor elke interactable entity opnieuw ingeladen.
	this->interactTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "pixelOrange.png").c_str());
}

void InteractableEntity::interact(Player* player)
{
	//TODO : oplossen op manier zonder casten
	//if (this->getEnabled())
	//{
	//	int percentage = (int)(((double)currentInteractTime / (double)interactTime) * 100);
	//	cout << percentage << endl;
	//}
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
		int perc = ((getPercentageCompleted()) * this->getHeight())/  100;

		SDL_Rect rect;
		rect.x = this->getX() - c->getX();
		rect.y = this->getY() - c->getY() + perc;
		rect.w = this->getWidth();
		rect.h = this->getHeight() - perc;

		//Cropping rect
		SDL_Rect croppingRect = rect;
		croppingRect.x = 0;
		croppingRect.y = perc;
		croppingRect.h = this->getHeight() + perc;

		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), this->highlightTexture, &croppingRect, &rect );

	}
	}

int InteractableEntity::getPercentageCompleted() {
	return (static_cast<double>(currentInteractTime) / static_cast<double>(interactTime)) * 100;
}

void InteractableEntity::degradeTool(Player* player) {
	Equipable* tool = dynamic_cast<Equipable*>(player->getInventory()->getSelectedItem());
	tool->setDurability(tool->getDurability() - 1);
	if (tool->getDurability() <= 0) {
		std::cout << "Destroying pickaxe, no durability!" << std::endl;
		player->getInventory()->deleteItem(tool->getId(), 1);
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

	this->currentInteractTime += GameTimer::Instance()->getFrameTime();
	if (this->currentInteractTime > this->interactTime) {
		this->currentInteractTime = 0;
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