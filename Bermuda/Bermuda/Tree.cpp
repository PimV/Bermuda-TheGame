#include "Tree.h"
#include "Tool.h"
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
	this->respawnTime = GameTimer::Instance()->getFullDayLength() * 10;
	this->interactTime = 10000;
	this->animationType = AnimationEnumType::Chop;
}

bool Tree::canInteract(Player* player) {
	if (player->getInventory()->axeSelected()) {
		this->setHighlightTexture(this->getCanInteractTexture());
	} else {
		this->setHighlightTexture(this->getCantInteractTexture());
	}
	return player->getInventory()->axeSelected();
}

void Tree::interact(Player* player) {
	if (player->getInventory()->axeSelected()) {
		player->setCorrectToolSelected(true);
		InteractableEntity::interact(player);
		if (this->trackInteractTimes()) {
			player->setCorrectToolSelected(false);
			this->setDestroyedState();
			player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Wood));
			player->getStatusTracker()->addAchievementCount(AchievementsEnum::TREECUT);

			//Degradability
				this->degradeTool(player);
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
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void Tree::setDestroyedState() 
{
	this->setHighlighted(false);
	this->timeDestroyed = GameTimer::Instance()->getGameTime();
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
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}
