#pragma once
#include "Cactus.h"
#include "InteractableEntity.h"

class InteractableCactus :
	public Cactus, public InteractableEntity
{
private:
	Image* cactusImage;
	Image* stumpImage;
	SDL_Texture* canInteractTexture;
	SDL_Texture* cantInteractTexture;
public:
	InteractableCactus(int id, double x, double y, Image* image, Image* stumpImage);
	void update(double dt);
	void respawn();
	void interact(Player* player);
	void setDestroyedState();
	bool canInteract(Player* player);
	virtual ~InteractableCactus();
};

