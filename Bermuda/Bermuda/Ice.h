#pragma once
#include "drawableentity.h"
#include "CollidableEntity.h"
#include "InteractableEntity.h"

class Ice :
	public DrawableEntity, public CollidableEntity, public InteractableEntity
{
private:
	Image* iceImage;
	Image* icePiecesImage;
public:
	Ice(int id, double x, double y, Image* rockImage, Image* rockPieces);
	void update(double dt);
	void interact(Player* player);
	virtual void setDestroyedState();
	bool canInteract(Player* player);
	virtual ~Ice();
};

