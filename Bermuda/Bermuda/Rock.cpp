#include "Rock.h"


Rock::Rock(int id, MainEntityContainer* mec, double x, double y, Image* rockImage, Image* rockPiecesImage)
	: DrawableEntity(id, rockImage), Collidable(0, 14, 32, 18), mec(mec), rockImage(rockImage), rockPiecesImage(rockPiecesImage)
{
	setX(x);
	setY(y);
	setCollidableValues();
	mec->getDrawableContainer()->add(this);
	mec->getCollidableContainer()->add(this);
}

void Rock::setCollidableValues()
{
	this->mapX = this->getX();
	this->mapY = this->getY();
	this->mapWidth = this->getWidth();
	this->mapHeight = this->getHeight();
}

//TODO: Use this->setDrawImage() to change to stump or tree. 

Rock::~Rock()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
