#pragma once
#include "entity.h"
#include "CollidableContainer.h"
#include "Image.h"
#include "MovementDirectionEnum.h"

class MovableEntity :
	virtual public Entity
{

public:
	MovableEntity(int id, double x, double y);
	virtual ~MovableEntity(void);

	virtual void update(double dt) = 0;

	void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt, int animationSpeed);
	void StopAnimation();
	MovementDirectionEnum getMovementDirection();

	double stopSpeed, minSpeed, moveSpeed, maxSpeed, sprintSpeed;
	bool movingLeft, movingRight, movingDown, movingUp;
	bool sprinting;

	bool canMove(double dt);
	void move(double dt);

	long getTimeSinceLastAction();
	void setTimeSinceLastAction(long time);
protected:
	virtual void setImage(Image* image) = 0;
	virtual void ResetDrawableEntityAndSetChunk() = 0;
	virtual bool checkCollision(double newX, double newY) = 0;


	virtual void setPosition(double newX, double newY);

	double dx, dy;

	bool keepAnimationWhenIdle;
	int firstImgID;
	int currentAnimationRow, animationIdleColumn;
	int animationWalkUpRow, animationWalkLeftRow, animationWalkDownRow, animationWalkRightRow;
	int animationWalkStartColumn, animationWalkEndColumn;
	int animationActionStartColumn, animationActionEndColumn;
	int frameAmountX, frameAmountY, CurrentFrame;
	int defaultAnimationSpeed, defaultAnimationActionSpeed;
	double animationSpeed, animationDelay;
	
	MovementDirectionEnum movementDirection;

	long timeSinceLastAction;
};