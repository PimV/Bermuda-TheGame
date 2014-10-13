#pragma once
#include "tile.h"
#include "CollidableEntity.h"

class CollidableTile :
	public virtual Tile,
	public virtual CollidableEntity
{
public:
	CollidableTile(int id, MainEntityContainer* mec, double x, double y, Image* image);

	virtual ~CollidableTile();
};

