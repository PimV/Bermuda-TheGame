#pragma once
#include "entity.h"
#include "IMovable.h"
#include "header_loader.h"
#include "Camera.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "SDLInitializer.h"
#include "MainEntityContainer.h"

class Inventory;

class Player :
	public IMovable,
	public DrawableEntity,
	public CollidableEntity
{
public:
	Player(int id, double moveSpeed, double x, double y, int chunkSize, Camera* camera, GameStateManager* gsm, MainEntityContainer* mec);
	//virtual void move(EnumDirection direction) = 0;
	void update(double dt);
	virtual void move(double dt);
	//void clickMove();
	void clickMove();
	void setPosition();
	void interact();
	void resetMovement();
	void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt);
	void StopAnimation();

	//void draw(SDLInitializer* sdlInitializer);
	bool checkCollision(CollidableContainer* container);
	~Player(void);

	bool movingLeft;
	bool movingRight;
	bool movingUp;
	bool movingDown;
	bool moveClick;
	bool interaction;
	int destX;
	int destY;

	Inventory* getInventory();

private:
	const char* path;
	Camera* camera;
	GameStateManager* gsm;

	int firstImgID;
	int currentPlayerAnimationRow, playerAnimationIdleColumn;
	int playerAnimationWalkUpRow, playerAnimationWalkLeftRow, playerAnimationWalkDownRow, playerAnimationWalkRightRow;
	int playerAnimationWalkStartColumn, playerAnimationWalkEndColumn;
	int playerAnimationActionStartColumn, playerAnimationActionEndColumn;
	int frameAmountX, frameAmountY, CurrentFrame;
	double animationSpeed, animationDelay;

	double getDistence(int currentX, int currentY, int destX, int destY);

	MainEntityContainer* mec;

	Inventory* inventory;
};
