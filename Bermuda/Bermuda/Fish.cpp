#include "Fish.h"
#include "PlayState.h"
#include "ItemFactory.h"
#include "Items.h"

Fish::Fish(int id, double x, double y, int chunkSize, Image* fishImage) :
	Entity(id,x,y,chunkSize), 
	DrawableEntity(id,x,y,chunkSize, fishImage), 
	InteractableEntity(id,x,y,chunkSize, -64, -64, 192, 192)
{
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);

	this->destroyed = false;
	this->respawnTime = 10000;
	this->interactTime = 9000;
}

void Fish::interact(Player* player) 
{
	//TODO: check if player has fishingrod or fishing harpoon
	InteractableEntity::interact(player);
	player->setCorrectToolSelected(true);
	if (this->trackInteractTimes()) {
		player->setCorrectToolSelected(false);
		this->setDestroyedState();		
		player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Fish));
		//TODO: add fish caught in statustracker
	} else {
		player->setCorrectToolSelected(false);
	}
}

void Fish::update(double dt) 
{
	if (this->destroyed) {
		if (this->timeDestroyed + respawnTime < GameTimer::Instance()->getGameTime()) {
			this->respawn();
		}
	}
}

void Fish::respawn() 
{
	this->destroyed = false;
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
}

void Fish::setDestroyedState() 
{
	this->timeDestroyed = GameTimer::Instance()->getGameTime();
	this->destroyed = true;
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	currentInteractTime = 0;
}

Fish::~Fish()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	if(this->destroyed) { 
		PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this); 
	}
	else { 
		PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this); 
	}
}
