#pragma once
#include "DrawableEntity.h"
#include "MainEntityContainer.h"

class Carrot :
	public DrawableEntity
{
private:
	Image* carrot;
	MainEntityContainer* mec;
public:
	Carrot(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* carrotImage);
	virtual ~Carrot();
};

