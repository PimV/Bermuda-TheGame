#include "MovableEntity.h"
#include "PlayState.h"

MovableEntity::MovableEntity(int id, double x, double y, int chunkSize)
	: Entity(id,x,y,chunkSize)
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
			this->PlayAnimation(this->animationWalkStartColumn, this->animationWalkEndColumn, this->currentAnimationRow, 0);
		}
		return;
	}

	this->setTempX(getX());
	this->setTempY(getY());

	double destX = getX() + dx;
	double destY = getY() + dy;

	bool col = false;

	while(this->getTempX() != destX || this->getTempY() != destY)
	{
		//x
		double diffX = this->getTempX() - destX;
		if(diffX > -10 && diffX < 10)
		{
			stepX = -diffX;
		}

		//y
		double diffY = this->getTempY() - destY;
		if(diffY > -10 && diffY < 10)
		{
			stepY = -diffY;
		}

		this->setTempX(getX() + stepX);
		this->setTempY(getY() + stepY);


		if (!this->checkCollision(PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()))
		{
			this->setPosition();
		}
		else
		{
			col = true;
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

	if(!col)
	{
		PlayAnimation(this->animationWalkStartColumn, this->animationWalkEndColumn, this->currentAnimationRow, dt);
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
	/*
	double animationDelay = 0;
	if (dt < 1)
		animationDelay = (maxSpeed / 100) * 40;
	else
		animationDelay = (maxSpeed / 100) * 70;

	this->animationSpeed -= animationDelay;
	*/

	double animationDelay = (maxSpeed / 100) * 40 * dt;
	animationSpeed -= animationDelay;
	if (animationSpeed < animationDelay)
	{
		this->currentAnimationRow = Row;

		if (EndFrame <= CurrentFrame)
			this->CurrentFrame = BeginFrame;
		else
			this->CurrentFrame++;

		this->setImage(GameStateManager::Instance()->getImageLoader()->getMapImage(firstImgID + (this->currentAnimationRow * this->frameAmountX) + this->CurrentFrame));
		this->animationSpeed = this->maxSpeed * 3;
	}
}

void MovableEntity::StopAnimation()
{
	this->setImage(GameStateManager::Instance()->getImageLoader()->getMapImage(firstImgID + (currentAnimationRow * frameAmountX) + animationIdleColumn));
}

bool MovableEntity::checkCollision(CollidableContainer* container) {
	//Calculate begin and end chunks for the player collision (+1 and -1 to make it a little bigger then the current chunk)
	int beginChunkX = this->getChunkX() - 1;
	int endChunkX = this->getChunkX() + 1;
	int beginChunkY = this->getChunkY() - 1;
	int endChunkY = this->getChunkY() + 1;

	//Loop through all chunks
	for (int i = beginChunkY; i <= endChunkY; i++)
	{
		for (int j = beginChunkX; j <= endChunkX; j++)
		{
			std::vector<CollidableEntity*>* vec = PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->getChunk(i, j);
			if (vec != nullptr)
			{
				for (CollidableEntity* e : *vec)
				{
					if (this->checkIntersects(e)) 
					{
						this->StopAnimation();
						return true;
					}
				}
			}
		}
	}

	return false;
}

void MovableEntity::setPosition() {
	this->setX(this->tempX);
	this->setY(this->tempY);

	//Chance chunks if needed
	if (floor(this->getY() / this->getChunkSize()) != this->getChunkY() || floor(this->getX() / this->getChunkSize()) != this->getChunkX())
	{
		//TODO : Put the player in another chunk in ALLL CONTAINERSSSS
		this->ResetDrawableEntityAndSetChunk();
	}
}