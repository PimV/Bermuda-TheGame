#include "CollidableTile.h"
#include <iostream>


CollidableTile::CollidableTile(int id, int chunkSize, MainEntityContainer* mec, double x, double y, Image* image) : 
	Entity(id), Tile(id, chunkSize, mec, x, y, image), CollidableEntity(id, 0, 0, image->getWidth(), image->getHeight())
{
	mec->getCollidableContainer()->add(this);
}

CollidableTile::~CollidableTile(void)
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
