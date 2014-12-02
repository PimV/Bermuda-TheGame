#pragma once
#include "drawableentity.h"
#include "MainEntityContainer.h"
#include "Image.h"

class Tile :
	public DrawableEntity
{
public:
	Tile(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* image);
	virtual ~Tile();
};
