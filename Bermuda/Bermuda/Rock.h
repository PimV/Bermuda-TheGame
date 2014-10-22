#pragma once
#include "drawableentity.h"
#include "CollidableEntity.h"
#include "MainEntityContainer.h"

class Rock :
	public DrawableEntity, public CollidableEntity
{
private:
	Image* rockImage;
	Image* rockPiecesImage;
	MainEntityContainer* mec;
public:
	Rock(int id, int x, int y, int chunkSize, MainEntityContainer* mec, Image* rockImage, Image* rockPieces);
	void setCollidableValues();
	~Rock();
};

