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

	//void clickMove();
	void clickMove();
	void setPosition();
	void interact();
	void resetMovement();

	void setCurrentInteractableEntity(InteractableEntity* newCurrent);
	InteractableEntity* getCurrentInteractableEntity();

	bool moveClick;
	bool interaction;
	int destX;
	int destY;

	Inventory* getInventory();
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
	StatusTracker* statusTracker;

	InteractableEntity* currentInteractableEntity;

	void updatePlayerStatuses();

	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkIntersects(CollidableEntity* collidableEntity);
};
