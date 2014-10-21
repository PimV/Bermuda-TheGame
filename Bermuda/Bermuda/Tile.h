#pragma once
#include "drawableentity.h"
#include "MainEntityContainer.h"
#include "Image.h"

class Tile :
	public DrawableEntity
{
public:
	Tile(int id, int chunkSize, MainEntityContainer* mec, double x, double y, Image* image);
	~Tile();
};
