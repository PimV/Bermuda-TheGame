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
	this->respawnTime = 5000;
	this->interactTime = 5000;
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
			player->getStatusTracker()->treeCut();

			//Degradability
			Equipable* tool = dynamic_cast<Equipable*>(player->getInventory()->getSelectedItem());
			tool->setDurability(tool->getDurability() - 1);
			std::cout << tool->getPercentageDegraded() << std::endl;
			if (tool->getDurability() <= 0) {
				std::cout << "Destroying axe, no durability!" << std::endl;
				player->getInventory()->deleteItem(tool->getId(), 1);
			}
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
