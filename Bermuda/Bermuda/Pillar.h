#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class Pillar :
	public DrawableEntity, public CollidableEntity
{
public:
	Pillar(int id, double x, double y, Image* image);
	virtual ~Pillar();
};

