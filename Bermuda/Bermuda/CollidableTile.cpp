#include "CollidableTile.h"
#include <iostream>


CollidableTile::CollidableTile(int id, Image* image, double collisionX, double collisionY, double collisionWidth, double collisionHeight) : 
	Tile(id, image), Collidable(collisionX, collisionY, collisionWidth, collisionHeight)
{
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
}
