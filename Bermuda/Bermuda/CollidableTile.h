#pragma once
#include "tile.h"
#include "Collidable.h"

class CollidableTile :
	public Tile,
	public Collidable
{
public:
	CollidableTile(int id, Image* image, double collisionX, double collisionY, double collisionWidth, double collisionHeight);
	
	void setCollidableValues();

	virtual ~CollidableTile();
};

