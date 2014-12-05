#include "GoldRock.h"
#include "PlayState.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"

GoldRock::GoldRock(int id, double x, double y, Image* rockImage, Image* rockPiecesImage) :
	Entity(id, x, y),
	DrawableEntity(id, x, y, rockImage),
	CollidableEntity(id, x, y, 0, 14, 32, 18), rockImage(rockImage), rockPiecesImage(rockPiecesImage),
	InteractableEntity(id, x, y, -35, -35, this->getWidth() + 70, this->getHeight() + 70)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->interactTime = 5000;

	this->animationType = AnimationEnumType::Mine;

	this->setCanInteractTexture(GameStateManager::Instance()->getImageLoader()->getInteractRockImage());
	this->setCantInteractTexture(GameStateManager::Instance()->getImageLoader()->getCantInteractRockImage());
	
	this->setHighlightTexture(this->getCantInteractTexture());
}

bool GoldRock::canInteract(Player* player) {
	if (player->getInventory()->pickAxeSelected()) {
		this->setHighlightTexture(this->getCanInteractTexture());
	} else {
		this->setHighlightTexture(this->getCantInteractTexture());
	}
	return player->getInventory()->pickAxeSelected();
}

void GoldRock::update(double dt) {

}

void GoldRock::interact(Player* player)
{
	if (player->getInventory()->pickAxeSelected()) {
		player->setCorrectToolSelected(true);
		InteractableEntity::interact(player);
		if (this->trackInteractTimes()) {
			player->setCorrectToolSelected(false);
			this->setDestroyedState();
			player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Gold));
			//TODO: add to statustracker
		}
	} else {
		player->setCorrectToolSelected(false);
	}

}

void GoldRock::setDestroyedState()
{
	this->destroyed = true;
	this->setCollisionX(0);
	this->setCollisionWidth(0);
	this->setCollisionY(0);
	this->setCollisionHeight(0);
	this->setDrawImage(this->rockPiecesImage);
	PlayState::Instance()->getMainEntityContainer()->getBackgroundContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
}

GoldRock::~GoldRock()
{
	if (this->destroyed)
	{
		PlayState::Instance()->getMainEntityContainer()->getBackgroundContainer()->remove(this);
	}
	else
	{
		PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
		PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
		PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	}
}
