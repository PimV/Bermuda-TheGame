#include "Wasp.h"
#include <time.h>
#include <iostream>
#include <random>
#include "PlayState.h"

Wasp::Wasp(int id, int chunkSize, Spawnpoint *spawnPoint) :
	NPC(id, chunkSize, 5, 1, 400, 50, spawnPoint),
	Entity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize),
	DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize, nullptr),
	CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize, 4, 10, 24, 18),
	MovableEntity(id, spawnPoint->getX(), spawnPoint->getY(), chunkSize)
{
	this->setWidth(32);
	this->setHeight(32);

	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 2;
	this->stopSpeed = 0.8;
	this->moveSpeed = 2;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	//this->interaction = false;

	this->setTempX(this->getX());
	this->setTempY(this->getY());

	this->firstImgID = GameStateManager::Instance()->getImageLoader()->loadTileset("bee.png", 32, 32);
	this->animationWalkUpRow = 0, this->animationWalkLeftRow = 1;
	this->animationWalkDownRow = 2, this->animationWalkRightRow = 3;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; this->animationWalkStartColumn = 1, this->animationWalkEndColumn = 2;
	//this->playerAnimationActionStartColumn = 1; this->playerAnimationActionEndColumn = 5;
	this->frameAmountX = 3, this->frameAmountY = 3, this->CurrentFrame = 0;
	this->animationSpeed = 10;//, this->animationDelay = 1;

	this->timeSinceLastAction = 0;

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	// Add to MovableContainer?

	this->StopAnimation();
}

void Wasp::update(double dt) {
	this->walk(dt);
}

void Wasp::walk(double dt)
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

void Wasp::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Wasp::ResetDrawableEntityAndSetChunk()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	this->setChunks();
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
}

bool Wasp::intersections(CollidableEntity* collidableEntity)
{
	return this->intersects(collidableEntity);
}

Wasp::~Wasp()
{

}