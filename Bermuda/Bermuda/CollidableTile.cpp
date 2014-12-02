#include "CollidableTile.h"
#include "PlayState.h"
#include <iostream>


CollidableTile::CollidableTile(int id, double x, double y, Image* image) : 
	Entity(id,x,y), 
	Tile(id, x, y, image), 
	CollidableEntity(id, x, y, 0, 0, image->getWidth(), image->getHeight())
{
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
}

CollidableTile::~CollidableTile(void)
{
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
