#pragma once
#include "drawableentity.h"
#include "CollidableEntity.h"
#include "MainEntityContainer.h"
#include "InteractableEntity.h"

class GoldRock :
	public DrawableEntity, public CollidableEntity, public InteractableEntity
{
private:
	Image* rockImage;
	Image* rockPiecesImage;
public:
	GoldRock(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* rockImage, Image* rockPieces);
	void setCollidableValues();
	void update(double dt);
	void interact(Player* player);
	virtual void setDestroyedState();
	virtual ~GoldRock();
};

