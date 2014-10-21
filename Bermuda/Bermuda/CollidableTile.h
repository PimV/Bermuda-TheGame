#pragma once
#include "tile.h"
#include "CollidableEntity.h"

class CollidableTile :
	public Tile, public CollidableEntity
{
public:
	CollidableTile(int id, int chunkSize, MainEntityContainer* mec, double x, double y, Image* image);

	virtual ~CollidableTile();
};

