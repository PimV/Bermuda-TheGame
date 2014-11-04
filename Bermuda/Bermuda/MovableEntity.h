#pragma once
#include "Entity.h"
#include "header_loader.h"
#include "GameStateManager.h"
#include "CollidableContainer.h"
#include "MainEntityContainer.h"

class MovableEntity :
	public virtual Entity
{
public:
	MovableEntity(int id, double x, double y, int chunkSize);
	virtual ~MovableEntity();

	void move(double dt);

	MainEntityContainer* mec;
	GameStateManager* gsm;
	
	virtual void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt) = 0;
	virtual void StopAnimation() = 0;

	int firstImgID;
	int currentPlayerAnimationRow, playerAnimationIdleColumn;
	int playerAnimationWalkUpRow, playerAnimationWalkLeftRow, playerAnimationWalkDownRow, playerAnimationWalkRightRow;
	int playerAnimationWalkStartColumn, playerAnimationWalkEndColumn;
	int playerAnimationActionStartColumn, playerAnimationActionEndColumn;
	int frameAmountX, frameAmountY, CurrentFrame;
	double animationSpeed, animationDelay;

	int dx, dy;
	double moveSpeed, minSpeed, maxSpeed, stopSpeed;
	bool movingDown, movingUp, movingRight, movingLeft;

	long timeSinceLastAction;
};

