#pragma once
#include "MovableEntity.h"
#include "CollidableEntity.h"
#include "DrawableEntity.h"
#include "Camera.h"
#include "StatusTracker.h"
#include "Inventory.h"
#include "Crafting.h"

class Inventory;

class Player :
	public MovableEntity,
	public DrawableEntity,
	public CollidableEntity
{
public:
	Player(int id, double moveSpeed, double x, double y, Camera* camera);
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

	//void clickMove();
	void clickMove();
	void setPosition(double newX, double newY);
	void interact();
	void resetMovement();

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

	//PlayerUpdateTimer* playerTimer;
	int health, hunger, thirst;
	long hungerUpdate, hungerUpdateTime;
	long thirstUpdate, thirstUpdateTime;

	double getDistence(int currentX, int currentY, int destX, int destY);

	Inventory* inventory;
	Crafting* crafting;
	StatusTracker* statusTracker;

	void updatePlayerStatuses(double dt);

	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkCollision(double newX, double newY);
};
