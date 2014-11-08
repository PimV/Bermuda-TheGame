#include "Carrot.h"
#include "Player.h"
#include "ItemCarrot.h"
//TODO : remove IOSTREAM
#include <iostream>

Carrot::Carrot(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* carrotImage)
	: Entity(id,x,y,chunkSize), DrawableEntity(id,x,y,chunkSize, carrotImage), InteractableEntity(id,x,y,chunkSize, -25, -25, this->getWidth() + 50, this->getHeight() + 50)
{
	this->setMainEntityContainer(mec);

	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void Carrot::update(double dt) {

}

void Carrot::interact(Player* player)
{
	player->getInventory()->addItem(new ItemCarrot());
	player->getStatusTracker()->carrotPicked();
	this->setDestroyedState();
	//std::cout << "interact met CARROT X: " << this->getX() << " Y: " << this->getY() << std::endl;
}

void Carrot::setDestroyedState()
{
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
}

Carrot::~Carrot()
{
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
}
