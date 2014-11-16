#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "MainEntityContainer.h"

class RockSpikes :
	public DrawableEntity, public CollidableEntity
{
public:
	RockSpikes(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* image);
	virtual ~RockSpikes();
};

