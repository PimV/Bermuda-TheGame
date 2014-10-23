#include "Rock.h"
//TODO : remove IOSTREAM
#include <iostream>


Rock::Rock(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* rockImage, Image* rockPiecesImage)
	: Entity(id,x,y,chunkSize), 
	DrawableEntity(id,x,y,chunkSize, rockImage), 
	CollidableEntity(id,x,y,chunkSize, 0, 14, 32, 18), mec(mec), rockImage(rockImage), rockPiecesImage(rockPiecesImage),
	InteractableEntity(id,x,y,chunkSize, 35)
{
	mec->getDrawableContainer()->add(this);
	mec->getCollidableContainer()->add(this);
	mec->getInteractableContainer()->add(this);
}

//TODO: Use this->setDrawImage() to change to rock pieces

void Rock::interact()
{
	std::cout << "interact met ROCK X: " << this->getX() << " Y: " << this->getY() << std::endl;
}

Rock::~Rock()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
