#pragma once
#include "entity.h"
#include "CollidableContainer.h"
#include "Image.h"

class MovableEntity :
	virtual public Entity
{

public:
	MovableEntity(int id, double x, double y, int chunkSize);
	virtual ~MovableEntity(void);

	virtual void directionsAndMove(double dt) = 0;
	virtual void update(double dt) = 0;

	void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt);
	void StopAnimation();

	double stopSpeed, minSpeed, moveSpeed, maxSpeed, sprintSpeed;
	bool movingLeft, movingRight, movingDown, movingUp;
	bool sprinting;
protected:
	virtual void setImage(Image* image) = 0;
	virtual void ResetDrawableEntityAndSetChunk() = 0;
	virtual bool checkCollision(double newX, double newY) = 0;

	virtual void move(double dt);
	virtual void setPosition(double newX, double newY);

	double dx, dy;

	bool keepAnimationWhenIdle;
	int firstImgID;
	int currentAnimationRow, animationIdleColumn;
	int animationWalkUpRow, animationWalkLeftRow, animationWalkDownRow, animationWalkRightRow;
	int animationWalkStartColumn, animationWalkEndColumn;
	int animationActionStartColumn, animationActionEndColumn;
	int frameAmountX, frameAmountY, CurrentFrame;
	double animationSpeed, animationDelay;
	
	long timeSinceLastAction;
};