#include "Rabbit.h"
#include "PlayState.h"
#include <time.h>
#include <iostream>
#include <random>
#include "PlayState.h"

Rabbit::Rabbit(int id, int chunkSize, Spawnpoint* spawnPoint, int firstImgID) :
	NPC(id, chunkSize, 5, 1, 50, spawnPoint),
	Entity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize),
	DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize, nullptr),
	CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize, 4, 20, 28, 12),
	MovableEntity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize)
{
	this->setWidth(36);
	this->setHeight(36);

	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 2;
	this->moveSpeed = 2;
	this->stopSpeed = 0.8;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	//this->interaction = false;

	this->setTempX(this->getX());
	this->setTempY(this->getY());

	this->firstImgID = firstImgID;
	this->animationWalkUpRow = 1, this->animationWalkLeftRow = 3;
	this->animationWalkDownRow = 0, this->animationWalkRightRow = 2;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; this->animationWalkStartColumn = 1, this->animationWalkEndColumn = 7;

	//this->playerAnimationActionStartColumn = 1; this->playerAnimationActionEndColumn = 5;
	this->frameAmountX = 8, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;//, this->animationDelay = 1;

	this->timeSinceLastAction = 0;

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);

	this->StopAnimation();
}

void Rabbit::update(double dt) {
	this->directionsAndMove(dt);
}

void Rabbit::directionsAndMove(double dt)
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

		if ((getX() - getSpawnPoint()->getX()) > getSpawnPoint()->getWalkRange())
		{
			movingRight = false;
			movingLeft = true;
		}
		else if ((getSpawnPoint()->getX() - getX()) > getSpawnPoint()->getWalkRange())
		{
			movingRight = true;
			movingLeft = false;
		}

		if ((getY() - getSpawnPoint()->getY()) > getSpawnPoint()->getWalkRange())
		{
			movingDown = false;
			movingUp = true;
		}
		else if ((getSpawnPoint()->getY() - getY()) > getSpawnPoint()->getWalkRange())
		{
			movingDown = true;
			movingUp = false;
		}

	}
	this->move(dt);
}

void Rabbit::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Rabbit::ResetDrawableEntityAndSetChunk()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	this->setChunks(); 
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
}

bool Rabbit::checkIntersects(CollidableEntity* collidableEntity)
{
	return this->intersects(collidableEntity);
}

Rabbit::~Rabbit()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
}