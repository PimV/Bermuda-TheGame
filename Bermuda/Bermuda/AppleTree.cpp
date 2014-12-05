#include "AppleTree.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"

AppleTree::AppleTree(int id, double x, double y, Image* treeImage, Image* treeEmptyImage, Image* stumpImage) :
	Entity(id,x,y), 
	DrawableEntity(id,x,y, treeImage), 
	InteractableEntity(id,x,y, 14, 60, 68, 78),
	CollidableEntity(id,x,y, 34, 102, 27, 15), treeImage(treeImage), treeEmptyImage(treeEmptyImage), stumpImage(stumpImage)
{
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);

	this->destroyed = false;
	this->respawnTime = 5000;
	this->interactTime = 3000;

	this->animationType = AnimationEnumType::Pick;

	canInteractTexture = GameStateManager::Instance()->getImageLoader()->getInteractTreeImage();
	cantInteractTexture = GameStateManager::Instance()->getImageLoader()->getCantInteractTreeImage();

	this->setHighlightTexture(cantInteractTexture);
}

bool AppleTree::canInteract(Player* player) {
	if (this->destroyed) {
		this->setHighlightTexture(cantInteractTexture);
	} else {
		this->setHighlightTexture(canInteractTexture);
	}
	return !this->destroyed;
}

void AppleTree::interact(Player* player) {
	if(!this->destroyed)
	{
		InteractableEntity::interact(player);
		player->setCorrectToolSelected(true);
		if (this->trackInteractTimes()) {
			player->setCorrectToolSelected(false);
			this->setDestroyedState();
			player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Apple));
			player->getStatusTracker()->applePicked();
		}
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
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	//PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

}

void AppleTree::setDestroyedState() 
{
	this->setHighlighted(false);
	this->timeDestroyed = GameTimer::Instance()->getGameTime();
	this->destroyed = true;
	this->setDrawImage(this->treeEmptyImage);
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->add(this);
	//PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	currentInteractTime = 0;
}


AppleTree::~AppleTree()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	if(this->destroyed) 
	{ 
		PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	}
}
