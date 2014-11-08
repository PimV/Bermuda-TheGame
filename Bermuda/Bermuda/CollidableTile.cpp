#include "CollidableTile.h"
#include <iostream>


CollidableTile::CollidableTile(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* image) : 
	Entity(id,x,y,chunkSize), Tile(id, x, y, chunkSize, mec, image), CollidableEntity(id, x, y, chunkSize, 0, 0, image->getWidth(), image->getHeight())
{
	this->getMainEntityContainer()->getCollidableContainer()->add(this);
}

CollidableTile::~CollidableTile(void)
{
	this->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
