#pragma once
#include "entity.h"
#include "CollidableContainer.h"

class MovableEntity :
	virtual public Entity
{

public:
	MovableEntity(int id, double x, double y, int chunkSize);
	virtual ~MovableEntity(void);

	virtual void update(double dt) = 0;
	void move(double dt);

protected:
	virtual void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt) = 0;
	virtual void StopAnimation() = 0;
	virtual void setPosition() = 0;
	virtual bool checkCollision(CollidableContainer* container) = 0;

	//Speed Variables
	double stopSpeed, minSpeed, moveSpeed, maxSpeed, sprintSpeed;
	//Direction Booleans
	bool movingLeft, movingRight, movingDown, movingUp;
	bool sprinting;
	//Direction Variables
	double dx, dy;

	int currentPlayerAnimationRow, playerAnimationIdleColumn;
	int playerAnimationWalkUpRow, playerAnimationWalkLeftRow, playerAnimationWalkDownRow, playerAnimationWalkRightRow;
	int playerAnimationWalkStartColumn, playerAnimationWalkEndColumn;
	int playerAnimationActionStartColumn, playerAnimationActionEndColumn;
	int frameAmountX, frameAmountY, CurrentFrame;
	double animationSpeed, animationDelay;
};

