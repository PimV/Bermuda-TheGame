#pragma once
#include "DrawableEntity.h"
#include "InteractableEntity.h"
#include "MainEntityContainer.h"

class Axe :
	public DrawableEntity, public InteractableEntity 
{
private:
	Image* axe;
	MainEntityContainer* mec;
public:
	Axe(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* axeImage);
	void update(double dt);
	virtual ~Axe();

	void interact(Player* player);
};

