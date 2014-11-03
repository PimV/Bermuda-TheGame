#include "Rabbit.h"
#include <time.h>
#include <iostream>

Rabbit::Rabbit(int id, int chunkSize, Spawnpoint* spawnPoint, GameStateManager* gsm, MainEntityContainer* mec) :
NPC(id, chunkSize, 5, 1, 500, 50, spawnPoint),
Entity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize),
DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize, nullptr),
CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize),
IMovable(2)
{
	this->gsm = gsm;
	this->mec = mec;

	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 3;
	this->stopSpeed = 0.8;

	this->setTempX(this->getX());
	this->setTempY(this->getY());

	this->setWidth(36);
	this->setHeight(36);
	
	this->destinationX = this->getX();
	this->destinationY = this->getY();

	this->setMainEntityContainer(mec);
	//this->getMainEntityContainer()->getInteractableContainer()->add(this);
	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	this->getMainEntityContainer()->getCollidableContainer()->add(this);

	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	//this->interaction = false;

	this->firstImgID = gsm->getImageLoader()->loadTileset("rabbitsheet.png", 36, 36);

	this->playerAnimationWalkUpRow = 1, this->playerAnimationWalkLeftRow = 3;
	this->playerAnimationWalkDownRow = 0, this->playerAnimationWalkRightRow = 2;
	this->currentPlayerAnimationRow = this->playerAnimationWalkDownRow;

	this->playerAnimationIdleColumn = 0; this->playerAnimationWalkStartColumn = 1, this->playerAnimationWalkEndColumn = 7;
	//this->playerAnimationActionStartColumn = 1; this->playerAnimationActionEndColumn = 5;
	this->frameAmountX = 8, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;//, this->animationDelay = 1;

	this->StopAnimation();
}

void Rabbit::update(double dt) {
	this->walk(dt);
	std::cout << this->getX() << std::endl;

	//if (destroyed) {
	//	this->timeSinceDestroy += GameStateManager::Instance()->getUpdateLength() * dt;
	//	if (this->timeSinceDestroy > respawnTime) {
	//		this->respawn();
	//	}
	//}
}

void Rabbit::PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt)
{
	double animationDelay = (maxSpeed / 100) * 40;
	animationSpeed -= animationDelay;
	if (animationSpeed < animationDelay)
	{
		this->currentPlayerAnimationRow = Row;
		if (EndFrame <= CurrentFrame)
			CurrentFrame = BeginFrame;
		else
			CurrentFrame++;

		this->setDrawImage(gsm->getImageLoader()->getMapImage(firstImgID + (currentPlayerAnimationRow * frameAmountX) + CurrentFrame));
		animationSpeed = maxSpeed * 3;
	}
}

void Rabbit::StopAnimation()
{
	this->setDrawImage(gsm->getImageLoader()->getMapImage(firstImgID + (currentPlayerAnimationRow * frameAmountX) + playerAnimationIdleColumn));
}

void Rabbit::setPosition() {
	//this->setX(getX() + dx);
	//this->setY(getY() + dy);

	this->setX(this->tempX);
	this->setY(this->tempY);

	//Chance chunks if needed
	if (floor(this->getY() / this->getChunkSize()) != this->getChunkY() || floor(this->getX() / this->getChunkSize()) != this->getChunkX())
	{
		//TODO : Put the player in another chunk in ALLL CONTAINERSSSS
		this->mec->getDrawableContainer()->remove(this);
		this->setChunks();
		this->mec->getDrawableContainer()->add(this);
	}
}

bool Rabbit::checkCollision(CollidableContainer* container) {
	//TODO: werkend maken met nieuwe collidablecontainer
	double currentX = this->getX();
	double currentY = this->getY();
	this->setX(this->tempX);
	this->setY(this->tempY);

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
			std::vector<CollidableEntity*>* vec = this->mec->getCollidableContainer()->getChunk(i, j);
			if (vec != nullptr)
			{
				for (CollidableEntity* e : *vec)
				{
					if (this->intersects(e)) {
						this->setX(currentX);
						this->setY(currentY);
						this->StopAnimation();
						return true;
					}
				}
			}
		}
	}

	return false;
}

void Rabbit::walk(double dt)
{

	if (this->getX() == this->destinationX && this->getY() == this->destinationY) {
		std::cout << "Rabbit is walking!" << std::endl;
		srand(time(NULL));

		double distanceX = rand() % (this->getWalkRange() * 2) + (this->getWalkRange() * -1);
		double distanceY = rand() % (this->getWalkRange() * 2) + (this->getWalkRange() * -1);

		this->destinationX = this->getSpawnPoint()->getX() + distanceX;
		this->destinationY = this->getSpawnPoint()->getY() + distanceY;
	}

	this->move(dt);
}

void Rabbit::move(double dt)
{
	if (this->getX() + this->getWidth() / 2 > this->destinationX - 5 && this->getX() + this->getWidth() / 2 < this->destinationX + 5) {
		movingRight = false;
		movingLeft = false;
	}
	else if (this->destinationX > this->getX() + this->getWidth() / 2)
	{
		movingRight = true;
		movingLeft = false;
	}
	else if (this->destinationX < this->getX() + this->getWidth() / 2)
	{
		movingLeft = true;
		movingRight = false;
	}

	if (this->getY() + this->getHeight() > this->destinationY - 5 && this->getY() + this->getHeight() < this->destinationY + 5) {
		movingDown = false;
		movingUp = false;
	}
	else if (this->destinationY > this->getY() + this->getHeight())
	{
		movingDown = true;
		movingUp = false;
	}
	else if (this->destinationY < this->getY() + this->getHeight())
	{
		movingUp = true;
		movingDown = false;
	}


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

	//if (dx != 0 && dy != 0) {

	//dx = dx / 2;
	//dy = dy / 2;

	//dx = dx / (moveSpeed / 2);
	//dy = dy / (moveSpeed / 2);
	//}

	//Move rabbit
	this->setTempX(getX() + dx);
	this->setTempY(getY() + dy);

	if (this->movingLeft)
		this->currentPlayerAnimationRow = this->playerAnimationWalkLeftRow;
	else if (this->movingRight)
		this->currentPlayerAnimationRow = this->playerAnimationWalkRightRow;
	else if (this->movingUp)
		this->currentPlayerAnimationRow = this->playerAnimationWalkUpRow;
	else if (this->movingDown)
		this->currentPlayerAnimationRow = this->playerAnimationWalkDownRow;

	PlayAnimation(this->playerAnimationWalkStartColumn, this->playerAnimationWalkEndColumn, this->currentPlayerAnimationRow, dt);
}

Rabbit::~Rabbit()
{

}