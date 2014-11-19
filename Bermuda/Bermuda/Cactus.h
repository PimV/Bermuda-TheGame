#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "MainEntityContainer.h"

class Cactus :
	public DrawableEntity, public CollidableEntity
{
public:
	Cactus(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* image);
	virtual ~Cactus();
};

