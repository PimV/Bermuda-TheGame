#pragma once
#include "entity.h"
#include "header_loader.h"
#include "Camera.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "SDLInitializer.h"
#include "MainEntityContainer.h"
#include "MovableEntity.h"

class Inventory;

class Player :
	public DrawableEntity,
	public CollidableEntity,
	public MovableEntity
{
public:
	Player(int id, double moveSpeed, double x, double y, int chunkSize, Camera* camera, GameStateManager* gsm, MainEntityContainer* mec);
	//virtual void move(EnumDirection direction) = 0;
	void update(double dt);
	void calculateMovingDirectionAndMove(double dt);
	//void clickMove();
	void clickMove();
	void setPosition();
	void interact();
	void resetMovement();

	virtual void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt);
	virtual void StopAnimation();

	//void draw(SDLInitializer* sdlInitializer);
	bool checkCollision(CollidableContainer* container);
	~Player(void);

	bool moveClick;
	int destX;
	int destY;

	double sprintSpeed;
	bool sprinting;

	bool interaction;

	Inventory* getInventory();

private:
	const char* path;
	Camera* camera;

	double getDistence(int currentX, int currentY, int destX, int destY);

	Inventory* inventory;
};
