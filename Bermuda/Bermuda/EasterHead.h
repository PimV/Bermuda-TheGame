#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"

class EasterHead :
	public DrawableEntity, public CollidableEntity
{
public:
	EasterHead(int id, double x, double y, Image* image);
	virtual ~EasterHead();
};

