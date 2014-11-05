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

	virtual void update(double dt) = 0;
protected:
	virtual void setImage(Image* image) = 0;
	virtual void ResetDrawableEntityAndSetChunk() = 0;
	virtual bool intersections(CollidableEntity* collidableEntity) = 0;

	void move(double dt);
	void setPosition();
	bool checkCollision(CollidableContainer* container);
	void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt);
	void StopAnimation();

	//Speed Variables
	double stopSpeed, minSpeed, moveSpeed, maxSpeed, sprintSpeed;
	//Direction Booleans
	bool movingLeft, movingRight, movingDown, movingUp;
	bool sprinting;
	//Direction Variables
	double dx, dy;

	int firstImgID;
	int currentAnimationRow, animationIdleColumn;
	int animationWalkUpRow, animationWalkLeftRow, animationWalkDownRow, animationWalkRightRow;
	int animationWalkStartColumn, animationWalkEndColumn;
	int animationActionStartColumn, animationActionEndColumn;
	int frameAmountX, frameAmountY, CurrentFrame;
	double animationSpeed, animationDelay;
};

