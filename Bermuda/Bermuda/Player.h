#pragma once
#include "entity.h"
#include "MovableEntity.h"
#include "header_loader.h"
#include "Camera.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "SDLInitializer.h"
#include "MainEntityContainer.h"
#include "StatusTracker.h"
#include "GameTimer.h"
#include "Inventory.h"
#include "Crafting.h"

class Inventory;

class Player :
	public MovableEntity,
	public DrawableEntity,
	public CollidableEntity
{
public:
	Player(int id, double moveSpeed, double x, double y, int chunkSize, Camera* camera);
	~Player(void);

	void update(double dt);
	void directionsAndMove(double dt);

	void setHealth(int value);
	void setHunger(int value);
	void setThirst(int value);

	void incrementHealth(int value);
	void incrementHunger(int value);
	void incrementThirst(int value);

	int getHealth();
	int getHunger();
	int getThirst();

	void drawHealthBar(int x, int y);
	void drawHungerBar(int x, int y);
	void drawThirstBar(int x, int y);

	//void clickMove();
	void clickMove();
	void setPosition();
	void interact();
	void resetMovement();

	void draw();

	bool moveClick;
	bool interaction;
	int destX;
	int destY;

	Inventory* getInventory();
	Crafting* getCraftingSystem();
	StatusTracker* getStatusTracker();

private:
	const char* path;
	Camera* camera;
	SDL_Texture* healthBar;
	SDL_Texture* hungerBar;
	SDL_Texture* thirstBar;
	SDL_Texture* healthBarContainer;
	SDL_Texture* thirstBarContainer;
	SDL_Texture* hungerBarContainer;

	bool healthAlphaFade;
	bool hungerAlphaFade;
	bool thirstAlphaFade;

	int healthAlpha;
	int hungerAlpha;
	int thirstAlpha;

	//PlayerUpdateTimer* playerTimer;
	int health, hunger, thirst;
	long hungerUpdate, hungerUpdateTime;
	long thirstUpdate, thirstUpdateTime;
	long healthUpdate, healthUpdateTime;

	double getDistence(int currentX, int currentY, int destX, int destY);

	Inventory* inventory;
	Crafting* crafting;
	StatusTracker* statusTracker;

	void updatePlayerStatuses(double dt);



	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkIntersects(CollidableEntity* collidableEntity);
};
