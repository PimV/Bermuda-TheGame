#include "Carrot.h"
#include "Player.h"
#include "ItemCarrot.h"
//TODO : remove IOSTREAM
#include <iostream>

Carrot::Carrot(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* carrotImage)
	: Entity(id,x,y,chunkSize), DrawableEntity(id,x,y,chunkSize, carrotImage), InteractableEntity(id,x,y,chunkSize, 25)
{
	mec->getDrawableContainer()->add(this);
	mec->getInteractableContainer()->add(this);
}

void Carrot::interact(Player* p)
{
	p->getInventory()->addItem(new ItemCarrot());
	std::cout << "interact met CARROT X: " << this->getX() << " Y: " << this->getY() << std::endl;
}


Carrot::~Carrot()
{
}
