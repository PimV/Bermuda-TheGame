#include "Ice.h"
#include "Player.h"
#include "ItemFactory.h"


Ice::Ice(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* rockImage, Image* rockPiecesImage) :
	Entity(id, x, y, chunkSize),
	DrawableEntity(id, x, y, chunkSize, rockImage),
	CollidableEntity(id, x, y, chunkSize, 0, 14, 32, 18), iceImage(rockImage), icePiecesImage(rockPiecesImage),
	InteractableEntity(id, x, y, chunkSize, -35, -35, this->getWidth() + 70, this->getHeight() + 70)
{
	this->setMainEntityContainer(mec);

	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	this->getMainEntityContainer()->getCollidableContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->interactTime = 1000;
	this->currentInteractTime = 0;
}

void Ice::update(double dt) {

}

void Ice::interact(Player* player)
{
	if (player->getInventory()->hasPickaxe()) {
		InteractableEntity::interact(player);
		if (this->trackInteractTimes()) {
			this->setDestroyedState();
			player->getInventory()->addItem(ItemFactory::Instance()->createWater());
			//TODO: add to statustracker
		}
	}
}

void Ice::setDestroyedState()
{
	this->destroyed = true;
	this->setCollisionX(0);
	this->setCollisionWidth(0);
	this->setCollisionY(0);
	this->setCollisionHeight(0);
	this->setDrawImage(this->icePiecesImage);
	this->getMainEntityContainer()->getBackgroundContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	this->getMainEntityContainer()->getCollidableContainer()->remove(this);
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
}


Ice::~Ice()
{
	if (this->destroyed)
	{
		this->getMainEntityContainer()->getBackgroundContainer()->remove(this);
	}
	else
	{
		this->getMainEntityContainer()->getInteractableContainer()->remove(this);
		this->getMainEntityContainer()->getCollidableContainer()->remove(this);
		this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	}
}
