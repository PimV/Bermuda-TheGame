#pragma once
#include "drawableentity.h"
#include "MainEntityContainer.h"
#include "Image.h"

class Tile :
	public DrawableEntity
{
public:
	Tile(int id, int x, int y, int chunkSize, MainEntityContainer* mec, Image* image);
	~Tile();
};
