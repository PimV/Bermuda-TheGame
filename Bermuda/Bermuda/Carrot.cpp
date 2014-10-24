#include "Carrot.h"
#include "Player.h"
#include "ItemCarrot.h"
//TODO : remove IOSTREAM
#include <iostream>

Carrot::Carrot(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* carrotImage)
	: Entity(id,x,y,chunkSize), DrawableEntity(id,x,y,chunkSize, carrotImage), InteractableEntity(id,x,y,chunkSize, 25)
{
	this->setMainEntityContainer(mec);

	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void Carrot::interact(Player* p)
{
	p->getInventory()->addItem(new ItemCarrot());
	//std::cout << "interact met CARROT X: " << this->getX() << " Y: " << this->getY() << std::endl;
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
}


Carrot::~Carrot()
{
}
