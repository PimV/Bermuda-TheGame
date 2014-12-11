#pragma once
#include "DrawableEntity.h"
#include "InteractableEntity.h"

class Pickaxe :
	public DrawableEntity, public InteractableEntity 
{
private:
	Image* axe;
public:
	Pickaxe(int id, double x, double y, Image* pickaxeImage);
	void update(double dt);
	virtual ~Pickaxe();

	void interact(Player* player);
};

