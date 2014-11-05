#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "MainEntityContainer.h"

class Pillar :
	public DrawableEntity, public CollidableEntity
{
public:
	Pillar(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* image);
	virtual ~Pillar();
};

