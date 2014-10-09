#include "CollidableTile.h"


CollidableTile::CollidableTile(int id, Image* image, double collisionX, double collisionY, double collisionWidth, double collisionHeight) : 
	Tile(id, image), Collidable(collisionX, collisionY, collisionWidth, collisionHeight)
{
}


CollidableTile::~CollidableTile(void)
{
}
