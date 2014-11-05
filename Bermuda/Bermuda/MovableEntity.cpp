#include "MovableEntity.h"
#include "PlayState.h"

MovableEntity::MovableEntity(int id, double x, double y, int chunkSize)
	: Entity(id,x,y,chunkSize)
{
}

MovableEntity::~MovableEntity(void)
{
}

void MovableEntity::move(double dt)
{
	if (movingLeft) {
		dx -= moveSpeed *dt;
		if (dx < -maxSpeed *dt) {
			dx = -maxSpeed *dt;
		}
	}
	else if (movingRight) {
		dx += moveSpeed *dt;
		if (dx > maxSpeed *dt) {
			dx = maxSpeed *dt;
		}
	}
	else {
		if (dx > 0) {
			dx -= stopSpeed *dt;
			if (dx < 0) {
				dx = 0;
			}
		}
		else if (dx < 0) {
			dx += stopSpeed *dt;
			if (dx > 0) {
				dx = 0;
			}
		}
	}

	if (movingUp) {
		dy -= moveSpeed *dt;
		if (dy < -maxSpeed *dt) {
			dy = -maxSpeed *dt;
		}
	}
	else if (movingDown) {
		dy += moveSpeed *dt;
		if (dy > maxSpeed *dt) {
			dy = maxSpeed *dt;
		}
	}
	else {
		if (dy > 0) {
			dy -= stopSpeed *dt;
			if (dy < 0) {
				dy = 0;
			}
		}
		else if (dy < 0) {
			dy += stopSpeed *dt;
			if (dy > 0) {
				dy = 0;
			}
		}
	}

	if (dx == 0 && dy == 0) {
		return;
	}

	//Move wasp
	this->setTempX(getX() + dx);
	this->setTempY(getY() + dy);

	if (!this->checkCollision(PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()))
	{
		this->setPosition();

		// set animation row
		if (this->movingLeft)
			this->currentAnimationRow = this->animationWalkLeftRow;
		else if (this->movingRight)
			this->currentAnimationRow = this->animationWalkRightRow;
		else if (this->movingUp)
			this->currentAnimationRow = this->animationWalkUpRow;
		else if (this->movingDown)
			this->currentAnimationRow = this->animationWalkDownRow;

		PlayAnimation(this->animationWalkStartColumn, this->animationWalkEndColumn, this->currentAnimationRow, dt);
	}
}

void MovableEntity::PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt)
{
	double animationDelay = (maxSpeed / 100) * 40;
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

void MovableEntity::setPosition() {
	//this->setX(getX() + dx);
	//this->setY(getY() + dy);

	this->setX(this->tempX);
	this->setY(this->tempY);

	//Chance chunks if needed
	if (floor(this->getY() / this->getChunkSize()) != this->getChunkY() || floor(this->getX() / this->getChunkSize()) != this->getChunkX())
	{
		//TODO : Put the player in another chunk in ALLL CONTAINERSSSS
		this->ResetDrawableEntityAndSetChunk();
	}
}
