#include "Rock.h"
#include "Player.h"
#include "ItemRock.h"
//TODO : remove IOSTREAM
#include <iostream>


Rock::Rock(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* rockImage, Image* rockPiecesImage)
	: Entity(id,x,y,chunkSize), 
	DrawableEntity(id,x,y,chunkSize, rockImage), 
	CollidableEntity(id,x,y,chunkSize, 0, 14, 32, 18), mec(mec), rockImage(rockImage), rockPiecesImage(rockPiecesImage),
	InteractableEntity(id,x,y,chunkSize, 35)
{
	this->setMainEntityContainer(mec);

	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	this->getMainEntityContainer()->getCollidableContainer()->add(this);
	this->getMainEntityContainer()->getInteractableContainer()->add(this);
}

//TODO: Use this->setDrawImage() to change to rock pieces

void Rock::interact(Player* p)
{
	//std::cout << "interact met ROCK X: " << this->getX() << " Y: " << this->getY() << std::endl;

	p->getInventory()->addItem(new ItemRock());
	//std::cout << "interact met CARROT X: " << this->getX() << " Y: " << this->getY() << std::endl;
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	this->getMainEntityContainer()->getInteractableContainer()->remove(this);
	this->getMainEntityContainer()->getCollidableContainer()->remove(this);
}

Rock::~Rock()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
