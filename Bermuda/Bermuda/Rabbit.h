#pragma once
#include "NPC.h"
#include "Evasive.h"
#include "IMovable.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "MainEntityContainer.h"

class Rabbit :
	public NPC,
	public Evasive,
	public IMovable,
	public DrawableEntity,
	public CollidableEntity
{
public:
	Rabbit(int id, int chunkSize, Spawnpoint *spawnPoint, GameStateManager* gsm, MainEntityContainer* mec);
	~Rabbit();

	void walk(double dt);
	virtual void move(double dt);
	void update(double dt);
	bool checkCollision(CollidableContainer* container);
	void setPosition();

private:
	void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt);
	void StopAnimation();

	int firstImgID;
	int currentPlayerAnimationRow, playerAnimationIdleColumn;
	int playerAnimationWalkUpRow, playerAnimationWalkLeftRow, playerAnimationWalkDownRow, playerAnimationWalkRightRow;
	int playerAnimationWalkStartColumn, playerAnimationWalkEndColumn;
	int playerAnimationActionStartColumn, playerAnimationActionEndColumn;
	int frameAmountX, frameAmountY, CurrentFrame;
	double animationSpeed, animationDelay;

	int tempCounter, dx, dy, maxSpeed, stopSpeed;
	bool walking, movingDown, movingUp, movingRight, movingLeft;
	double destinationX, destinationY;
	GameStateManager* gsm;
	MainEntityContainer* mec;

	long timeSinceLastAction;
};

