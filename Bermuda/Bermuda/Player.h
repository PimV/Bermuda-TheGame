#pragma once
#include "entity.h"
#include "header_loader.h"
#include "Camera.h"
#include "MovableEntity.h"
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
	Player(int id, double moveSpeed, double x, double y, int chunkSize, Camera* camera, GameStateManager* gsm, MainEntityContainer* mec);
	//virtual void move(EnumDirection direction) = 0;

	void update(double dt);
	//void move(double dt);
	void walk(double dt);

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
	//void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt);
	//void StopAnimation();

	//void draw(SDLInitializer* sdlInitializer);
	//bool checkCollision(CollidableContainer* container);
	~Player(void);

	//bool movingLeft;
	//bool movingRight;
	//bool movingUp;
	//bool movingDown;
	bool moveClick;
	bool interaction;
	int destX;
	int destY;

	Inventory* getInventory();
	StatusTracker* getStatusTracker();

private:
	const char* path;
	Camera* camera;
	GameStateManager* gsm;

	//PlayerUpdateTimer* playerTimer;
	int health, hunger, thirst;
	long hungerUpdate, hungerUpdateTime;
	long thirstUpdate, thirstUpdateTime;

	//int firstImgID;
	//int currentPlayerAnimationRow, playerAnimationIdleColumn;
	//int playerAnimationWalkUpRow, playerAnimationWalkLeftRow, playerAnimationWalkDownRow, playerAnimationWalkRightRow;
	//int playerAnimationWalkStartColumn, playerAnimationWalkEndColumn;
	//int playerAnimationActionStartColumn, playerAnimationActionEndColumn;
	//int frameAmountX, frameAmountY, CurrentFrame;
	//double animationSpeed, animationDelay;

	double getDistence(int currentX, int currentY, int destX, int destY);

	MainEntityContainer* mec;

	Inventory* inventory;
	StatusTracker* statusTracker;

	void updatePlayerStatuses();



	void setImage(Image* image);
	void ResetDrawableEntityAndSetChunk();
	bool checkIntersects(CollidableEntity* collidableEntity);
};
