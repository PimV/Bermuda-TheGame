#pragma once
#include "Cactus.h"
#include "InteractableEntity.h"

class InteractableCactus :
	public Cactus, public InteractableEntity
{
private:
	Image* cactusImage;
	Image* stumpImage;
public:
	InteractableCactus(int id, double x, double y, Image* image, Image* stumpImage);
	void setCollidableValues();
	void update(double dt);
	void respawn();
	void interact(Player* player);
	virtual void setDestroyedState();
	virtual ~InteractableCactus();
};

