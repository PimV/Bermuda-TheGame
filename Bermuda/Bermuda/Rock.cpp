#include "Rock.h"


Rock::Rock(int id, MainEntityContainer* mec, double x, double y, Image* rockImage, Image* rockPiecesImage)
	: Entity(id), DrawableEntity(id, rockImage), CollidableEntity(id, 0, 14, 32, 18), mec(mec), rockImage(rockImage), rockPiecesImage(rockPiecesImage)
{
	setX(x);
	setY(y);
	mec->getDrawableContainer()->add(this);
	mec->getCollidableContainer()->add(this);
}

//TODO: Use this->setDrawImage() to change to rock pieces

Rock::~Rock()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
