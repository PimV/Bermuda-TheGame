#pragma once
#include "drawableentity.h"
#include "CollidableEntity.h"
#include "MainEntityContainer.h"
#include "InteractableEntity.h"

class Ice :
	public DrawableEntity, public CollidableEntity, public InteractableEntity
{
private:
	Image* iceImage;
	Image* icePiecesImage;
public:
	Ice(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* rockImage, Image* rockPieces);
	void setCollidableValues();
	void update(double dt);
	void interact(Player* player);
	virtual void setDestroyedState();
	virtual ~Ice();
};

