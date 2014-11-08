#include "Axe.h"
#include "Player.h"
#include "ToolAxe.h"
//TODO : remove IOSTREAM
#include <iostream>

Axe::Axe(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* axeImage)
	: Entity(id,x,y,chunkSize), DrawableEntity(id,x,y,chunkSize, axeImage), InteractableEntity(id,x,y,chunkSize, -25, -25, this->getWidth() + 50, this->getHeight() + 50)
{
	this->setMainEntityContainer(mec);

	this->getMainEntityContainer()->getBackgroundContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void Axe::update(double dt) {

}

void Axe::interact(Player* player)
{
	player->getInventory()->addItem(new ToolAxe());
	this->getMainEntityContainer()->getBackgroundContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
}


Axe::~Axe()
{
	this->getMainEntityContainer()->getBackgroundContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
}
