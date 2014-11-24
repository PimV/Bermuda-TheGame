#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "MainEntityContainer.h"

class EasterHead :
	public DrawableEntity, public CollidableEntity
{
public:
	EasterHead(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* image);
	virtual ~EasterHead();
};

