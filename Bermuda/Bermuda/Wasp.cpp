#include "Wasp.h"
#include <time.h>
#include <iostream>
#include <random>

Wasp::Wasp(int id, int chunkSize, Spawnpoint* spawnPoint, GameStateManager* gsm, MainEntityContainer* mec) :
NPC(id, chunkSize, 5, 1, 400, 50, spawnPoint),
Entity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize),
DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize, nullptr),
CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize, 4, 10, 24, 18),
MovableEntity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize)
{
	this->gsm = gsm;
	this->mec = mec;

	this->setWidth(32);
	this->setHeight(32);

	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 2;
	this->stopSpeed = 0.8;
	this->moveSpeed = 2;
	this->minSpeed = 1;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	//this->interaction = false;

	this->setTempX(this->getX());
	this->setTempY(this->getY());

	this->firstImgID = gsm->getImageLoader()->loadTileset("bee.png", 32, 32);
	this->playerAnimationWalkUpRow = 0, this->playerAnimationWalkLeftRow = 1;
	this->playerAnimationWalkDownRow = 2, this->playerAnimationWalkRightRow = 3;
	this->currentPlayerAnimationRow = this->playerAnimationWalkDownRow;
	this->playerAnimationIdleColumn = 0; this->playerAnimationWalkStartColumn = 1, this->playerAnimationWalkEndColumn = 2;
	//this->playerAnimationActionStartColumn = 1; this->playerAnimationActionEndColumn = 5;
	this->frameAmountX = 3, this->frameAmountY = 3, this->CurrentFrame = 0;
	this->animationSpeed = 10;//, this->animationDelay = 1;

	this->timeSinceLastAction = 0;

	mec->getDrawableContainer()->add(this);
	mec->getCollidableContainer()->add(this);

	this->StopAnimation();
}

void Wasp::update(double dt) {
	this->calculateMovingDirectionAndMove(dt);
	//std::cout << "Rabbit X: " << this->getX() << " Y: " << this->getY() << " - Destination X: " << this->destinationX << " Destionation Y: " << this->destinationY << std::endl;

	//if (destroyed) {
	//	this->timeSinceDestroy += GameStateManager::Instance()->getUpdateLength() * dt;
	//	if (this->timeSinceDestroy > respawnTime) {
	//		this->respawn();
	//	}
	//}
}

void Wasp::PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt)
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

void Wasp::StopAnimation()
{
	this->setDrawImage(gsm->getImageLoader()->getMapImage(firstImgID + (currentPlayerAnimationRow * frameAmountX) + playerAnimationIdleColumn));
}

void Wasp::setPosition() {
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

bool Wasp::checkCollision(CollidableContainer* container) {
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

void Wasp::calculateMovingDirectionAndMove(double dt)
{
	random_device dev;
	default_random_engine dre(dev());

	uniform_int_distribution<int> dist1(1000, 5000);
	int timeWait = dist1(dre);

	if (timeSinceLastAction < timeWait)
	{
		timeSinceLastAction += GameStateManager::Instance()->getUpdateLength() * dt;
	}
	else {
		movingUp = false;
		movingDown = false;
		movingRight = false;
		movingLeft = false;

		timeSinceLastAction = 0;

		uniform_int_distribution<int> dist2(1, 10);
		int randomNumberMoveDirection = dist2(dre);

		this->StopAnimation();

		switch (randomNumberMoveDirection)
		{
		case 1:
			movingRight = true;
			movingLeft = false;
			break;
		case 2:
			movingRight = false;
			movingLeft = true;
			break;
		case 3:
			movingDown = true;
			movingUp = false;
			break;
		case 4:
			movingDown = false;
			movingUp = true;
			break;
		default:
			movingUp = false;
			movingDown = false;
			movingRight = false;
			movingLeft = false;
			dx = 0;
			dy = 0;
			break;
		}

		if ((getX() - getSpawnPoint()->getX()) > getWalkRange())
		{
			movingRight = false;
			movingLeft = true;
		}
		else if ((getSpawnPoint()->getX() - getX()) > getWalkRange())
		{
			movingRight = true;
			movingLeft = false;
		}

		if ((getY() - getSpawnPoint()->getY()) > getWalkRange())
		{
			movingDown = false;
			movingUp = true;
		}
		else if ((getSpawnPoint()->getY() - getY()) > getWalkRange())
		{
			movingDown = true;
			movingUp = false;
		}

	}
	this->move(dt);
}

Wasp::~Wasp()
{

}