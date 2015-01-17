#pragma once
#include "DrawableEntity.h"
#include "InteractableEntity.h"
#include "Items.h"

class Fish :
	public DrawableEntity, public InteractableEntity
{
private:
	Image* fishImage;
public:
	Fish(int id, double x, double y, Image* fishImage);

	void update(double dt);
	void respawn();
	void interact(Player* player);
	void setDestroyedState();
	bool canInteract(Player* player);

	virtual ~Fish();
};

