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
	double stepX = 0;
	double stepY = 0;

	if (movingLeft) {
		dx -= moveSpeed *dt;
		if (dx < -maxSpeed *dt) {
			dx = -maxSpeed *dt;
		}
		stepX = -10;
	}
	else if (movingRight) {
		dx += moveSpeed *dt;
		if (dx > maxSpeed *dt) {
			dx = maxSpeed *dt;
		}
		stepX = 10;
	}
	else
	{
		dx = 0;
	}
	/*else {
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
	}*/

	if (movingUp) {
		dy -= moveSpeed *dt;
		if (dy < -maxSpeed *dt) {
			dy = -maxSpeed *dt;
		}
		stepY = -10;
	}
	else if (movingDown) {
		dy += moveSpeed *dt;
		if (dy > maxSpeed *dt) {
			dy = maxSpeed *dt;
		}
		stepY = 10;
	}
	else
	{
		dy = 0;
	}
	/*else {
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
	}*/


	if (dx == 0 && dy == 0) {
		if(this->keepAnimationWhenIdle) 
		{  
			PlayAnimation(this->animationWalkStartColumn, this->animationWalkEndColumn, this->currentAnimationRow, dt);
		}
		return;
	}

	//this->setTempX(getX() + dx);
	//this->setTempY(getY() + dy);

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