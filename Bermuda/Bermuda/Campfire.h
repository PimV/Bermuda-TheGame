#pragma once
#include "AnimatingEntity.h"
#include "CollidableEntity.h"

class Campfire :
	public AnimatingEntity, public CollidableEntity
{
public:
	Campfire(int id, double x, double y, int chunkSize, int firstImgID);
	virtual ~Campfire();
};

