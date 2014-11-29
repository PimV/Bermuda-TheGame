#include "Rock.h"
#include "PlayState.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"

Rock::Rock(int id, double x, double y, Image* rockImage, Image* rockPiecesImage) :
	Entity(id,x,y), 
	DrawableEntity(id,x,y, rockImage), 
	CollidableEntity(id,x,y, 0, 14, 32, 18), rockImage(rockImage), rockPiecesImage(rockPiecesImage),
	InteractableEntity(id,x,y, -35, -35, this->getWidth() + 70, this->getHeight() + 70)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->interactTime = 1000;
	this->currentInteractTime = 0;
}

void Rock::update(double dt) {

}

void Rock::interact(Player* player)
{
	if (player->getInventory()->pickAxeSelected()) {
		InteractableEntity::interact(player);
		if (this->trackInteractTimes()) {
			this->setDestroyedState();
			player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Rock));
			player->getStatusTracker()->rockMined();
		}
	}
}

void Rock::setDestroyedState()
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

Rock::~Rock()
{
	if(this->destroyed)
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
