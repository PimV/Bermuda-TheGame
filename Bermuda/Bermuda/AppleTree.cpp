#include "AppleTree.h"
#include "GameStateManager.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"


AppleTree::AppleTree(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* treeImage, Image* treeEmptyImage, Image* stumpImage) :
	Entity(id,x,y,chunkSize), 
	DrawableEntity(id,x,y,chunkSize, treeImage), 
	InteractableEntity(id,x,y,chunkSize, 14, 80, 68, 48),
	CollidableEntity(id,x,y,chunkSize, 34, 102, 27, 15), treeImage(treeImage), treeEmptyImage(treeEmptyImage), stumpImage(stumpImage)
{
	this->setMainEntityContainer(mec);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	this->getMainEntityContainer()->getCollidableContainer()->add(this);

	this->destroyed = false;
	this->respawnTime = 5000;
	this->interactTime = 500;
}

void AppleTree::interact(Player* player) {
	InteractableEntity::interact(player);

	if (this->trackInteractTimes()) {
		this->setDestroyedState();
		player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Apple));
		player->getStatusTracker()->applePicked();
	}
}

void AppleTree::update(double dt) {
	if (destroyed) {
		if (this->timeDestroyed + this->respawnTime < GameTimer::Instance()->getGameTime()) {
			this->respawn();
		}
	}
}

void AppleTree::respawn() {
	this->destroyed = false;
	this->setDrawImage(this->treeImage);
	this->getMainEntityContainer()->getRespawnContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);

}

void AppleTree::setDestroyedState() 
{
	this->timeDestroyed = GameTimer::Instance()->getGameTime();
	this->destroyed = true;
	this->setDrawImage(this->treeEmptyImage);
	this->getMainEntityContainer()->getRespawnContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	currentInteractTime = 0;
}


AppleTree::~AppleTree()
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
