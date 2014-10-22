#pragma once
#include "tile.h"
#include "CollidableEntity.h"

class CollidableTile :
	public Tile, public CollidableEntity
{
public:
	CollidableTile(int id, int x, int y, int chunkSize, MainEntityContainer* mec, Image* image);

	virtual ~CollidableTile();
};

