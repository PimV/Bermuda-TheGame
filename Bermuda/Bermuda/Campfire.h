#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class Campfire :
	public DrawableEntity, public CollidableEntity
{
public:
	Campfire(int id, double x, double y, int chunkSize, Image* image);
	virtual ~Campfire();
};

