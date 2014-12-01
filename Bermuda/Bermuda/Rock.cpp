#include "Rock.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"


Rock::Rock(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* rockImage, Image* rockPiecesImage) :
	Entity(id,x,y,chunkSize), 
	DrawableEntity(id,x,y,chunkSize, rockImage), 
	CollidableEntity(id,x,y,chunkSize, 0, 14, 32, 18), rockImage(rockImage), rockPiecesImage(rockPiecesImage),
	InteractableEntity(id,x,y,chunkSize, -35, -35, this->getWidth() + 70, this->getHeight() + 70)
{
	this->setMainEntityContainer(mec);

	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	this->getMainEntityContainer()->getCollidableContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->interactTime = 5000;
	this->animationType = AnimationEnumType::Mine;
}

void Rock::update(double dt) {

}

void Rock::interact(Player* player)
{
	if (player->getInventory()->pickAxeSelected()) {
		InteractableEntity::interact(player);
		player->setCorrectToolSelected(true);
		if (this->trackInteractTimes()) {
			player->setCorrectToolSelected(false);
			this->setDestroyedState();
			player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Rock));
			player->getStatusTracker()->rockMined();
		}
	} else {
		player->setCorrectToolSelected(false);
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
	this->getMainEntityContainer()->getBackgroundContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	this->getMainEntityContainer()->getCollidableContainer()->remove(this);
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
}

Rock::~Rock()
{
	if(this->destroyed)
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
