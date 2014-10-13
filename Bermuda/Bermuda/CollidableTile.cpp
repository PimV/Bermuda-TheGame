#include "CollidableTile.h"
#include <iostream>


CollidableTile::CollidableTile(int id, MainEntityContainer* mec, double x, double y, Image* image) : 
	Tile(id, mec, x, y, image), Collidable(0, 0, image->getWidth(), image->getHeight())
{
	setCollidableValues();
	mec->getCollidableContainer()->add(this);
}

void CollidableTile::setCollidableValues()
{
	this->mapX = this->getX();
	this->mapY = this->getY();
	this->mapWidth = this->getWidth();
	this->mapHeight = this->getHeight();
}

CollidableTile::~CollidableTile(void)
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
