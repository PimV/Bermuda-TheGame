#pragma once
#include "drawableentity.h"
#include "Image.h"

class Tile :
	public DrawableEntity
{
public:
	Tile(int id, Image* image);
	~Tile();
};

