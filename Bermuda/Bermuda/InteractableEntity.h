#pragma once
#include "Entity.h"
#include "header_loader.h"
#include "AnimationEnum.h"
#include "Image.h"
class Player;
class GameStateManager;
class InteractableEntity :
	virtual public Entity
{
protected:
	bool destroyed;
	long currentInteractTime;
	long interactTime;
	long timeDestroyed;
	long respawnTime;

	AnimationEnumType animationType;

private:
	int interactStartX;
	int interactStartY;
	int interactWidth;
	int interactHeight;

	SDL_Rect interactRect;
	SDL_Texture* interactTexture;
	SDL_Texture* highlightTexture;

public:
	InteractableEntity(int id, double x, double y, int interactStartX, int interactStartY, int interactWidth, int interactHeight);

	virtual void update(double dt) = 0;
	void drawInteractableArea();

	void setHighlightTexture(SDL_Texture* texture);
	SDL_Texture* getHighlightTexture();

	virtual bool canInteract(Player* player);


	bool trackInteractTimes();

	int getInteractStartX();
	int getInteractStartY();
	int getInteractWidth();
	int getInteractHeight();

	void highlight();

	virtual void interact(Player* p);
	virtual void setDestroyedState();

	virtual AnimationEnumType getAnimationEnumType();

	virtual ~InteractableEntity();
};
