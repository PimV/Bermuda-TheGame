#pragma once
#include "DrawableEntity.h"
#include "InteractableEntity.h"

class Axe :
	public DrawableEntity, public InteractableEntity 
{
private:
	Image* axe;
public:
	Axe(int id, double x, double y, Image* axeImage);
	void update(double dt);
	virtual ~Axe();

	void interact(Player* player);
};

