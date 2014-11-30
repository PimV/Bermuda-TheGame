#include "InteractableCactus.h"
#include "Player.h"
#include "ItemFactory.h"

InteractableCactus::InteractableCactus(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* cactusImage, Image* stumpImage) :
	Entity(id, x, y, chunkSize),
	Cactus(id, x, y, chunkSize, mec, cactusImage),
	InteractableEntity(id, x, y, chunkSize, 0, 37, 64, 70)
{
	this->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->cactusImage = cactusImage;
	this->stumpImage = stumpImage;
	this->destroyed = false;
	this->respawnTime = 5000;
	this->interactTime = 500;
	this->timeSinceDestroy = 0;
	this->currentInteractTime = 0;

	this->animationType = AnimationEnumType::Chop;
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
	this->getMainEntityContainer()->getRespawnContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void InteractableCactus::interact(Player* player)
{
	if (player->getInventory()->axeSelected()) {
		if (player->getInventory()->hasAxe()) {
			player->setCorrectToolSelected(true);
			InteractableEntity::interact(player);
			if (this->trackInteractTimes()) {
				player->setCorrectToolSelected(false);
				this->setDestroyedState();
				player->getInventory()->addItem(ItemFactory::Instance()->createWater());
				//TODO: add to statustracker
			}
		}
	} else {
		player->setCorrectToolSelected(false);
	}
}

void InteractableCactus::setDestroyedState()
{
	// pims code, doesn't work with GameTimer
	this->destroyed = true;
	this->setDrawImage(this->stumpImage);
	this->getMainEntityContainer()->getRespawnContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	currentInteractTime = 0;
}

InteractableCactus::~InteractableCactus()
{
	if (this->destroyed)
	{
		this->getMainEntityContainer()->getRespawnContainer()->remove(this);
	}
	else
	{
		this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	}
}
