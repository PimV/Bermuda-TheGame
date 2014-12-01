#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class Cactus :
	public DrawableEntity, public CollidableEntity
{
public:
	Cactus(int id, double x, double y, Image* image);
	virtual ~Cactus();
};

