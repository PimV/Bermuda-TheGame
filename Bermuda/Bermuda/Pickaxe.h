#pragma once
#include "DrawableEntity.h"
#include "InteractableEntity.h"
#include "MainEntityContainer.h"

class Pickaxe :
	public DrawableEntity, public InteractableEntity 
{
private:
	Image* axe;
	MainEntityContainer* mec;
public:
	Pickaxe(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* pickaxeImage);
	void update(double dt);
	virtual ~Pickaxe();

	void interact(Player* player);
};

