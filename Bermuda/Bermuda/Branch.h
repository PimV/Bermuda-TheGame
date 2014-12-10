#pragma once
#include "DrawableEntity.h"
#include "InteractableEntity.h"
#include "Player.h"
#include "Image.h"

class Branch :
	public DrawableEntity, public InteractableEntity 
{
private:
	Image* branch;
public:
	Branch(int id, double x, double y, Image* branchImage);
	void update(double dt);
	virtual ~Branch();

	void interact(Player* player);
	void setDestroyedState();
};

