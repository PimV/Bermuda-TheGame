#include "MovableEntity.h"
#include "PlayState.h"

MovableEntity::MovableEntity(int id, double x, double y) : 
	Entity(id,x,y)
{
	this->keepAnimationWhenIdle = false;
}

MovableEntity::~MovableEntity(void)
{
}

void MovableEntity::move(double dt)
{
	this->dx = 0;
	this->dy = 0;
	double stepX = 0;
	double stepY = 0;

	if (movingLeft) {
		dx -= moveSpeed *dt;
		stepX = -10;
	}
	else if (movingRight) {
		dx += moveSpeed *dt;
		stepX = 10;
	}

	if (movingUp) {
		dy -= moveSpeed *dt;
		stepY = -10;
	}
	else if (movingDown) {
		dy += moveSpeed *dt;
		stepY = 10;
	} 

	//No movement
	if (dx == 0 && dy == 0) {
		if(this->keepAnimationWhenIdle) 
		{  
			PlayAnimation(this->animationWalkStartColumn, this->animationWalkEndColumn, this->currentAnimationRow, dt);
		}
		return;
	}

	double destX = getX() + dx;
	double destY = getY() + dy;

	bool collision = false;

	while (this->getX() != destX || this->getY() != destY)
	{
		//x
		double diffX = this->getX() - destX;
		if(diffX > -10 && diffX < 10)
		{
			stepX = -diffX;
		}

		//y
		double diffY = this->getY() - destY;
		if(diffY > -10 && diffY < 10)
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
		this->currentAnimationRow = this->animationWalkLeftRow;
	}
	else if (this->movingRight)
	{
		this->currentAnimationRow = this->animationWalkRightRow;
	}
	else if (this->movingUp)
	{
		this->currentAnimationRow = this->animationWalkUpRow;
	}
	else if (this->movingDown)
	{
		this->currentAnimationRow = this->animationWalkDownRow;
	}

	if (!collision || this->keepAnimationWhenIdle)
	{
		PlayAnimation(this->animationWalkStartColumn, this->animationWalkEndColumn, this->currentAnimationRow, dt);
	}
	else
	{
		this->StopAnimation();
	}

	//PlayAnimation(this->animationWalkStartColumn, this->animationWalkEndColumn, this->currentAnimationRow, dt);

	//if (!this->checkCollision(PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()))
	//{
	//	this->setPosition();

	//	// set animation row
	//	if (this->movingLeft)
	//		this->currentAnimationRow = this->animationWalkLeftRow;
	//	else if (this->movingRight)
	//		this->currentAnimationRow = this->animationWalkRightRow;
	//	else if (this->movingUp)
	//		this->currentAnimationRow = this->animationWalkUpRow;
	//	else if (this->movingDown)
	//		this->currentAnimationRow = this->animationWalkDownRow;

	//	PlayAnimation(this->animationWalkStartColumn, this->animationWalkEndColumn, this->currentAnimationRow, dt);
	//}
}

void MovableEntity::PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt)
{
	double animationDelay = (maxSpeed / 100) * 40 * dt;
	animationSpeed -= animationDelay;
	if (animationSpeed < animationDelay)
	{
		this->currentAnimationRow = Row;
		if (EndFrame <= CurrentFrame)
			CurrentFrame = BeginFrame;
		else
			CurrentFrame++;

		this->setImage(GameStateManager::Instance()->getImageLoader()->getMapImage(firstImgID + (currentAnimationRow * frameAmountX) + CurrentFrame));
		animationSpeed = maxSpeed * 3;
	}
}

void MovableEntity::StopAnimation()
{
	this->setImage(GameStateManager::Instance()->getImageLoader()->getMapImage(firstImgID + (currentAnimationRow * frameAmountX) + animationIdleColumn));
}

void MovableEntity::setPosition(double newX, double newY) {
	this->setX(newX);
	this->setY(newY);

	//Chance chunks if needed
	int chunkSize = PlayState::Instance()->getMainEntityContainer()->getChunkSize();
	if (floor(this->getY() / chunkSize) != this->getChunkY() || floor(this->getX() / chunkSize) != this->getChunkX())
	{
		//TODO : Put the player in another chunk in ALLL CONTAINERSSSS
		this->ResetDrawableEntityAndSetChunk();
	}
}