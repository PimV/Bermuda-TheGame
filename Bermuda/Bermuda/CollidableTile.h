#pragma once
#include "tile.h"
#include "Collidable.h"

class CollidableTile :
	public Tile,
	public Collidable
{
public:
	CollidableTile(int id, MainEntityContainer* mec, double x, double y, Image* image);
	
	void setCollidableValues();

	virtual ~CollidableTile();
};

