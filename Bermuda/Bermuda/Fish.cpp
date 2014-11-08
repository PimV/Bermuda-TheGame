#include "Fish.h"
#include "PlayState.h"
#include "ItemFish.h"

Fish::Fish(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* fishImage) :
	Entity(id,x,y,chunkSize), 
	DrawableEntity(id,x,y,chunkSize, fishImage), 
	InteractableEntity(id,x,y,chunkSize, -64, -64, 192, 192)
{
	this->setMainEntityContainer(mec);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	//PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
	//PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);

	this->destroyed = false;
	this->respawnTime = 10000;
	this->interactTime = 500;

	this->timeSinceDestroy = 0;
	this->currentInteractTime = 0;
}

void Fish::interact(Player* player) 
{
	//TODO: check if player has fishingrod or fishing harpoon
	InteractableEntity::interact(player);

	if (this->trackInteractTimes()) {
		this->setDestroyedState();		
		player->getInventory()->addItem(new ItemFish());
		//TODO: add fish caught in statustracker
	}
}

void Fish::update(double dt) 
{
	if (this->destroyed) {
		this->timeSinceDestroy += GameStateManager::Instance()->getUpdateLength() * dt;
		if (this->timeSinceDestroy > respawnTime) {
			this->respawn();
		}
	}
}

void Fish::respawn() 
{
	this->destroyed = false;
	this->timeSinceDestroy = 0;
	this->getMainEntityContainer()->getRespawnContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
	this->getMainEntityContainer()->getDrawableContainer()->add(this);
}

void Fish::setDestroyedState() 
{
	this->destroyed = true;
	this->getMainEntityContainer()->getRespawnContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	currentInteractTime = 0;
}


Fish::~Fish()
{
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	this->getMainEntityContainer()->getRespawnContainer()->remove(this); 
	this->getMainEntityContainer()->getInteractableContainer()->remove(this); 

}
