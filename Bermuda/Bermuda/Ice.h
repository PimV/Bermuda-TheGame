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
	SDL_Texture* canInteractTexture;
	SDL_Texture* cantInteractTexture;
public:
	Ice(int id, double x, double y, Image* rockImage, Image* rockPieces);
	void setCollidableValues();
	void update(double dt);
	void interact(Player* player);
	virtual void setDestroyedState();
	virtual ~Ice();
};

