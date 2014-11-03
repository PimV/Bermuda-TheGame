#pragma once
#include "drawableentity.h"
#include "CollidableEntity.h"
#include "MainEntityContainer.h"
#include "InteractableEntity.h"

class Rock :
	public DrawableEntity, public CollidableEntity, public InteractableEntity
{
private:
	Image* rockImage;
	Image* rockPiecesImage;
public:
	Rock(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* rockImage, Image* rockPieces);
	void setCollidableValues();
	void update(double dt);
	void interact(Player* player);
	void setDestroyedState();
	~Rock();
};

