#include "InteractableCactus.h"
#include "PlayState.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"

InteractableCactus::InteractableCactus(int id, double x, double y, Image* cactusImage, Image* stumpImage) :
	Entity(id, x, y),
	Cactus(id, x, y, cactusImage),
	InteractableEntity(id, x, y, 0, 37, 64, 70)
{
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->cactusImage = cactusImage;
	this->stumpImage = stumpImage;
	this->destroyed = false;
	this->respawnTime = 5000;
	this->interactTime = 500;
	this->timeSinceDestroy = 0;
	this->currentInteractTime = 0;
}

void InteractableCactus::update(double dt) {
	if (this->destroyed) {
		this->timeSinceDestroy += GameStateManager::Instance()->getUpdateLength() * dt;
		if (this->timeSinceDestroy > respawnTime) {
			this->respawn();
		}
	}
}

void InteractableCactus::respawn() {
	this->destroyed = false;
	this->timeSinceDestroy = 0;
	this->setDrawImage(this->cactusImage);
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void InteractableCactus::interact(Player* player)
{
	if (player->getInventory()->axeSelected()) {
		if (player->getInventory()->hasAxe()) {
			InteractableEntity::interact(player);
			if (this->trackInteractTimes()) {
				this->setDestroyedState();
				player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Water));
				//TODO: add to statustracker
			}
		}
	}
}

void InteractableCactus::setDestroyedState()
{
	// pims code, doesn't work with GameTimer
	this->destroyed = true;
	this->setDrawImage(this->stumpImage);
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	currentInteractTime = 0;
}

InteractableCactus::~InteractableCactus()
{
	if (this->destroyed)
	{
		PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	}
	else
	{
		PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	}
}
