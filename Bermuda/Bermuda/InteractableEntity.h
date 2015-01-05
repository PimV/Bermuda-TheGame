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

	int percentageCompleted;

	AnimationEnumType animationType;

private:
	int interactStartX;
	int interactStartY;
	int interactWidth;
	int interactHeight;

	SDL_Rect interactRect;
	SDL_Texture* interactTexture;

	SDL_Texture* highlightTexture;

	SDL_Texture* canInteractTexture;
	SDL_Texture* cantInteractTexture;

	Image* highlightImage;

public:
	InteractableEntity(int id, double x, double y, int interactStartX, int interactStartY, int interactWidth, int interactHeight);

	virtual void update(double dt) = 0;
	void drawInteractableArea();

	void setHighlightTexture(SDL_Texture* texture);
	SDL_Texture* getHighlightTexture();

	void setHighlightImage(Image* img);
	Image* getHighlightImage();

	void setCanInteractTexture(SDL_Texture* can);
	void setCantInteractTexture(SDL_Texture* cant);
	SDL_Texture* getCanInteractTexture();
	SDL_Texture* getCantInteractTexture();

	virtual bool canInteract(Player* player);


	bool trackInteractTimes();
	int getPercentageCompleted();

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
