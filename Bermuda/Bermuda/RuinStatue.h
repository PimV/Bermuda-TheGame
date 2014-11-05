#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "MainEntityContainer.h"

class RuinStatue :
	public DrawableEntity, public CollidableEntity
{
public:
	RuinStatue(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* image);
	virtual ~RuinStatue();
};

