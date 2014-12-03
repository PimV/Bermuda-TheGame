#pragma once
#include "DrawableEntity.h"
#include "Image.h"

class Tile :
	public DrawableEntity
{
public:
	Tile(int id, double x, double y, Image* image);
	virtual ~Tile();
};
