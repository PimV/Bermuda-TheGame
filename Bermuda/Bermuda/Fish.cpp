#include "Fish.h"
#include "PlayState.h"


Fish::Fish(int id, double x, double y, int chunkSize, Image* fishImage) :
	Entity(id,x,y,chunkSize), 
	DrawableEntity(id,x,y,chunkSize, fishImage), 
	InteractableEntity(id,x,y,chunkSize, -64, -64, 192, 192)
{
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);

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
		std::cout << "FISH ADDED!" << std::endl;
		//TODO: add item fish in inventory
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
	this->setDrawImage(this->fishImage);
	this->getMainEntityContainer()->getRespawnContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
	this->getMainEntityContainer()->getDrawableContainer()->add(this);
}

void Fish::setDestroyedState() 
{
	this->destroyed = true;
	//TODO: fish does only have 1 image.... nullptr works???
	this->setDrawImage(nullptr);
	this->getMainEntityContainer()->getRespawnContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	currentInteractTime = 0;
}


Fish::~Fish()
{
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	if(this->destroyed) 
	{ 
		this->getMainEntityContainer()->getRespawnContainer()->remove(this); 
	}
	else 
	{ 
		this->getMainEntityContainer()->getInteractableContainer()->remove(this); 
	}
}
