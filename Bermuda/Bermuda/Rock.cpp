#include "Rock.h"


Rock::Rock(int id, int x, int y, int chunkSize, MainEntityContainer* mec, Image* rockImage, Image* rockPiecesImage)
	: Entity(id,x,y,chunkSize), DrawableEntity(id,x,y,chunkSize, rockImage), CollidableEntity(id,x,y,chunkSize, 0, 14, 32, 18), mec(mec), rockImage(rockImage), rockPiecesImage(rockPiecesImage)
{
	mec->getDrawableContainer()->add(this);
	mec->getCollidableContainer()->add(this);
}

//TODO: Use this->setDrawImage() to change to rock pieces

Rock::~Rock()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
