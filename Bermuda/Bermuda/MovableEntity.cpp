#include "MovableEntity.h"
#include "PlayState.h"

MovableEntity::MovableEntity(int id, double x, double y) :
Entity(id, x, y)
{
	this->keepAnimationWhenIdle = false;

	// set the value just to be sure
	this->defaultAnimationSpeed = 40;
	this->defaultAnimationActionSpeed = 40;

	this->timeSinceLastAction = 0;
}

MovementDirectionEnum MovableEntity::getMovementDirection()
{
	return this->movementDirection;
}

//Returns true if its possible to move (partially) in the current movement direction.
bool MovableEntity::canMove(double dt)
{
	double dirX = 0;
	double dirY = 0;
	double stepX = 0;
	double stepY = 0;

	if (this->movingLeft) {
		dirX -= this->moveSpeed *dt;
		stepX = -10;
	}
	else if (this->movingRight) {
		dirX += this->moveSpeed *dt;
		stepX = 10;
	}

	if (this->movingUp) {
		dirY -= this->moveSpeed *dt;
		stepY = -10;
	}
	else if (this->movingDown) {
		dirY += this->moveSpeed *dt;
		stepY = 10;
	}

	//No movement is always possible.
	if (this->dx == 0 && this->dy == 0)
	{
		return true;
	}

	double destX = this->getX() + dirX;
	double destY = this->getY() + dirY;

	//x
	double diffX = this->getX() - destX;
	if (diffX > -10 && diffX < 10)
	{
		stepX = -diffX;
	}

	//y
	double diffY = this->getY() - destY;
	if (diffY > -10 && diffY < 10)
	{
		stepY = -diffY;
	}

	return !this->checkCollision(this->getX() + stepX, this->getY() + stepY);
}

void MovableEntity::move(double dt)
{
	this->dx = 0;
	this->dy = 0;
	double stepX = 0;
	double stepY = 0;

	if (this->movingLeft) {
		this->dx -= this->moveSpeed *dt;
		stepX = -10;
	}
	else if (this->movingRight) {
		this->dx += this->moveSpeed *dt;
		stepX = 10;
	}

	if (this->movingUp) {
		this->dy -= this->moveSpeed *dt;
		stepY = -10;
	}
	else if (this->movingDown) {
		this->dy += this->moveSpeed *dt;
		stepY = 10;
	}

	//No movement
	if (this->dx == 0 && this->dy == 0) {
		if (this->keepAnimationWhenIdle)
		{
			this->PlayAnimation(this->animationWalkStartColumn, this->animationWalkEndColumn, this->currentAnimationRow, dt, this->defaultAnimationSpeed);
		}
		return;
	}

	double destX = getX() + this->dx;
	double destY = getY() + this->dy;

	bool collision = false;

	while (this->getX() != destX || this->getY() != destY)
	{
		//x
		double diffX = this->getX() - destX;
		if (diffX > -10 && diffX < 10)
		{
			stepX = -diffX;
		}

		//y
		double diffY = this->getY() - destY;
		if (diffY > -10 && diffY < 10)
		{
			stepY = -diffY;
		}

		if (!this->checkCollision(this->getX() + stepX, this->getY() + stepY))
		{
			this->setPosition(this->getX() + stepX, this->getY() + stepY);
		}
		else
		{
			collision = true;
			break;
		}
	}
	// set animation row
	if (this->movingLeft)
	{
		this->movementDirection = MovementDirectionEnum::Left;
		this->currentAnimationRow = this->animationWalkLeftRow;
	}
	else if (this->movingRight)
	{
		this->movementDirection = MovementDirectionEnum::Right;
		this->currentAnimationRow = this->animationWalkRightRow;
	}
	else if (this->movingUp)
	{
		this->movementDirection = MovementDirectionEnum::Up;
		this->currentAnimationRow = this->animationWalkUpRow;
	}
	else if (this->movingDown)
	{
		this->movementDirection = MovementDirectionEnum::Down;
		this->currentAnimationRow = this->animationWalkDownRow;
	}

	if (!collision || this->keepAnimationWhenIdle)
	{
		this->PlayAnimation(this->animationWalkStartColumn, this->animationWalkEndColumn, this->currentAnimationRow, dt, this->defaultAnimationSpeed);
	}
	else
	{
		this->StopAnimation();
	}
}

void MovableEntity::PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt, int animationSpeed)
{
	double animationDelay = (maxSpeed / 100) * animationSpeed * dt;
	this->animationSpeed -= animationDelay;
	if (this->animationSpeed < animationDelay)
	{
		this->currentAnimationRow = Row;

		if (EndFrame <= CurrentFrame)
		{
			this->CurrentFrame = BeginFrame;
		}
		else
		{
			this->CurrentFrame++;
		}

		this->setImage(PlayState::Instance()->getImageLoader()->getMapImage(this->firstImgID + (this->currentAnimationRow * this->frameAmountX) + this->CurrentFrame));
		this->animationSpeed = this->maxSpeed * 3;
	}
}

void MovableEntity::StopAnimation()
{
	this->setImage(PlayState::Instance()->getImageLoader()->getMapImage(this->firstImgID + (this->currentAnimationRow * this->frameAmountX) + this->animationIdleColumn));
}

void MovableEntity::setPosition(double newX, double newY) {
	this->setX(newX);
	this->setY(newY);

	//Chance chunks if needed
	int chunkSize = PlayState::Instance()->getMainEntityContainer()->getChunkSize();
	if (floor(this->getY() / chunkSize) != this->getChunkY() || floor(this->getX() / chunkSize) != this->getChunkX())
	{
		this->ResetDrawableEntityAndSetChunk();
	}
}

long MovableEntity::getTimeSinceLastAction()
{
	return this->timeSinceLastAction;
}

void MovableEntity::setTimeSinceLastAction(long time)
{
	this->timeSinceLastAction = time;
}

MovableEntity::~MovableEntity()
{
}