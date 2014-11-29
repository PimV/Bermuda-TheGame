#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class RuinStatue :
	public DrawableEntity, public CollidableEntity
{
public:
	RuinStatue(int id, double x, double y, Image* image);
	virtual ~RuinStatue();
};

