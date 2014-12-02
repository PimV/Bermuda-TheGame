#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class SnowTree :
	public DrawableEntity, public CollidableEntity
{
public:
	SnowTree(int id, double x, double y, Image* image);
	virtual ~SnowTree();
};

