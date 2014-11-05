#include "Tree.h"
#include "GameStateManager.h"
#include "ItemWood.h"
#include "Player.h"

Tree::Tree(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* treeImage, Image* stumpImage) : 
	Entity(id,x,y,chunkSize), 
	DrawableEntity(id,x,y,chunkSize, treeImage), 
	InteractableEntity(id,x,y,chunkSize, 14, 60, 68, 78),
	CollidableEntity(id,x,y,chunkSize, 34, 102, 27, 15), treeImage(treeImage), stumpImage(stumpImage)
{
	this->setMainEntityContainer(mec);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	this->getMainEntityContainer()->getCollidableContainer()->add(this);

	this->destroyed = false;
	this->respawnTime = 5000;
	this->interactTime = 500;

	this->timeSinceDestroy = 0;
	this->currentInteractTime = 0;
}

void Tree::interact(Player* player) {
	if (player->getInventory()->hasAxe()) {
		InteractableEntity::interact(player);

		if (this->trackInteractTimes()) {
			this->setDestroyedState();
			player->getInventory()->addItem(new ItemWood());
			player->getStatusTracker()->treeCut();
		}
	}
}

void Tree::update(double dt) {
	if (this->destroyed) {
		this->timeSinceDestroy += GameStateManager::Instance()->getUpdateLength() * dt;
		if (this->timeSinceDestroy > respawnTime) {
			this->respawn();
		}
	}
}

void Tree::respawn() {
	this->destroyed = false;
	this->timeSinceDestroy = 0;
	this->setDrawImage(this->treeImage);
	this->getMainEntityContainer()->getRespawnContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void Tree::setDestroyedState() 
{
	// pims code, doesn't work with GameTimer
	this->destroyed = true;
	this->setDrawImage(this->stumpImage);
	this->getMainEntityContainer()->getRespawnContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	currentInteractTime = 0;

	/*
	this->destroyed = true;
	this->setDrawImage(this->stumpImage);
	this->nextRespawnUpdate = GameTimer::Instance()->getGameTime() + this->respawnTime;
	this->getMainEntityContainer()->getRespawnContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	currentInteractTime = 0;
	*/
}

Tree::~Tree()
{
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	this->getMainEntityContainer()->getCollidableContainer()->remove(this);
	if(this->destroyed) 
	{ 
		this->getMainEntityContainer()->getRespawnContainer()->remove(this); 
	}
	else 
	{ 
		this->getMainEntityContainer()->getInteractableContainer()->remove(this); 
	}
}
