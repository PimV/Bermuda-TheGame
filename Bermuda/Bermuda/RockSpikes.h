#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class RockSpikes :
	public DrawableEntity, public CollidableEntity
{
public:
	RockSpikes(int id, double x, double y, Image* image);
	virtual ~RockSpikes();
};

