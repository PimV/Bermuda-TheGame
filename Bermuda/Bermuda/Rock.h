#pragma once
#include "drawableentity.h"
#include "Collidable.h"
#include "MainEntityContainer.h"

class Rock :
	public DrawableEntity, public Collidable
{
private:
	Image* rockImage;
	Image* rockPiecesImage;
	MainEntityContainer* mec;
public:
	Rock(int id, MainEntityContainer* mec,  double x, double y, Image* rockImage, Image* rockPieces);
	void setCollidableValues();
	~Rock();
};

