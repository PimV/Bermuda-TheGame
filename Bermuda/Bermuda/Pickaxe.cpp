#include "Pickaxe.h"
#include "Player.h"
#include "ToolPickaxe.h"
#include "ItemFactory.h"

Pickaxe::Pickaxe(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* pickaxeImage)
	: Entity(id,x,y,chunkSize), DrawableEntity(id,x,y,chunkSize, pickaxeImage), InteractableEntity(id,x,y,chunkSize, -25, -25, this->getWidth() + 50, this->getHeight() + 50)
{
	this->setMainEntityContainer(mec);

	this->getMainEntityContainer()->getBackgroundContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void Pickaxe::update(double dt) {

}

void Pickaxe::interact(Player* player)
{
	player->getInventory()->addItem(ItemFactory::Instance()->createPickaxe());
	this->getMainEntityContainer()->getBackgroundContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
}


Pickaxe::~Pickaxe()
{
}
