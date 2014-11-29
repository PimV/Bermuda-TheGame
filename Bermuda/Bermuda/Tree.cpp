#include "Tree.h"
#include "PlayState.h"
#include "ItemWood.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"

Tree::Tree(int id, double x, double y, Image* treeImage, Image* stumpImage) : 
	Entity(id,x,y), 
	DrawableEntity(id,x,y, treeImage), 
	InteractableEntity(id,x,y, 14, 60, 68, 78),
	CollidableEntity(id,x,y, 34, 102, 27, 15), treeImage(treeImage), stumpImage(stumpImage)
{
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);

	this->destroyed = false;
	this->respawnTime = 5000;
	this->interactTime = 500;

	this->timeSinceDestroy = 0;
	this->currentInteractTime = 0;
}

void Tree::interact(Player* player) {
	if (player->getInventory()->axeSelected()) {
		InteractableEntity::interact(player);

		if (this->trackInteractTimes()) {
			this->setDestroyedState();
			player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Wood));
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
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void Tree::setDestroyedState() 
{
	// pims code, doesn't work with GameTimer
	this->destroyed = true;
	this->setDrawImage(this->stumpImage);
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	currentInteractTime = 0;
}

Tree::~Tree()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	if(this->destroyed) 
	{ 
		PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	}
	else 
	{ 
		PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	}
}
