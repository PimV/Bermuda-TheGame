#include "Tree.h"
#include "ItemWood.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"

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
	this->interactTime = 5000;
	this->animationType = AnimationEnumType::Chop;
}

void Tree::interact(Player* player) {
	if (player->getInventory()->axeSelected()) {
		player->setCorrectToolSelected(true);
		InteractableEntity::interact(player);
		if (this->trackInteractTimes()) {
			player->setCorrectToolSelected(false);
			this->setDestroyedState();
			player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Wood));
			player->getStatusTracker()->treeCut();
		}
	} else {
		player->setCorrectToolSelected(false);
	}
}

void Tree::update(double dt) {
	if (this->destroyed) {
		if (this->timeDestroyed + respawnTime < GameTimer::Instance()->getGameTime()) {
			this->respawn();
		}
	}
}

void Tree::respawn() {
	this->destroyed = false;
	this->setDrawImage(this->treeImage);
	this->getMainEntityContainer()->getRespawnContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void Tree::setDestroyedState() 
{
	this->timeDestroyed = GameTimer::Instance()->getGameTime();
	this->destroyed = true;
	this->setDrawImage(this->stumpImage);
	this->getMainEntityContainer()->getRespawnContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	currentInteractTime = 0;
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
