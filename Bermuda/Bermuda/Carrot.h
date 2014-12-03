#pragma once
#include "DrawableEntity.h"
#include "InteractableEntity.h"
#include "Player.h"
#include "Image.h"

class Carrot :
	public DrawableEntity, public InteractableEntity 
{
private:
	Image* carrot;
	SDL_Texture* canInteractTexture;
	SDL_Texture* cantInteractTexture;
public:
	Carrot(int id, double x, double y, Image* carrotImage);
	void update(double dt);
	virtual ~Carrot();

	void interact(Player* player);
	void setDestroyedState();
};

