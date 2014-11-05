#pragma once
#include "entity.h"
#include "CollidableContainer.h"

class MovableEntity :
	virtual public Entity
{

public:
	MovableEntity(int id, double x, double y, int chunkSize);
	virtual ~MovableEntity(void);

	void move(double dt);

protected:

	virtual void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt) = 0;
	virtual void StopAnimation() = 0;
	virtual void setPosition() = 0;
	virtual bool checkCollision(CollidableContainer* container) = 0;

	//Speed Variables
	double stopSpeed;
	double minSpeed;
	double moveSpeed;
	double maxSpeed;
	double sprintSpeed;
	bool sprinting;
	//Direction Booleans
	bool movingLeft;
	bool movingRight;
	bool movingDown;
	bool movingUp;
	//Direction Variables
	double dx;
	double dy;

	int currentPlayerAnimationRow, playerAnimationIdleColumn;
	int playerAnimationWalkUpRow, playerAnimationWalkLeftRow, playerAnimationWalkDownRow, playerAnimationWalkRightRow;
	int playerAnimationWalkStartColumn, playerAnimationWalkEndColumn;
	int playerAnimationActionStartColumn, playerAnimationActionEndColumn;
	int frameAmountX, frameAmountY, CurrentFrame;
	double animationSpeed, animationDelay;
};

