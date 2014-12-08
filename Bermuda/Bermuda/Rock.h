#pragma once
#include "drawableentity.h"
#include "CollidableEntity.h"
#include "InteractableEntity.h"

class Rock :
	public DrawableEntity, public CollidableEntity, public InteractableEntity
{
private:
	Image* rockImage;
	Image* rockPiecesImage;
public:
	Rock(int id, double x, double y, Image* rockImage, Image* rockPieces);
	void update(double dt);
	void interact(Player* player);

	bool canInteract(Player* player);
	virtual void setDestroyedState();
	virtual ~Rock();
};

