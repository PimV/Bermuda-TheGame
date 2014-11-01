#include "Tree.h"
#include "GameStateManager.h"
#include "ItemWood.h"
#include "Player.h"
#include <iostream>

Tree::Tree(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* treeImage, Image* stumpImage)	: 
	Entity(id,x,y,chunkSize), 
	DrawableEntity(id,x,y,chunkSize, treeImage), 
	InteractableEntity(id,x,y,chunkSize, 15),
	CollidableEntity(id,x,y,chunkSize, 34, 102, 27, 15), mec(mec), treeImage(treeImage), stumpImage(stumpImage)
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
	InteractableEntity::interact(player);

	if (this->trackInteractTimes()) {
		this->setDestroyedState();
		player->getInventory()->addItem(new ItemWood());
	}
}

void Tree::update(double dt) {
	if (destroyed) {
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
	this->destroyed = true;
	this->setDrawImage(this->stumpImage);
	this->getMainEntityContainer()->getRespawnContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	currentInteractTime = 0;
}

//TODO: Use this->setDrawImage() to change to stump or tree. 

Tree::~Tree()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
