#pragma once
#include "DrawableEntity.h"
#include "InteractableEntity.h"
#include "MainEntityContainer.h"

class Carrot :
	public DrawableEntity, public InteractableEntity 
{
private:
	Image* carrot;
	MainEntityContainer* mec;
public:
	Carrot(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* carrotImage);
	virtual ~Carrot();

	void interact();
};

