#include "Wasp.h"
#include "PlayState.h"
#include <time.h>
#include <iostream>
#include <random>
#include "WanderAround.h"

Wasp::Wasp(int id, Spawnpoint* spawnPoint, int firstImgID) :
	NPC(id, 5, 1, 50, spawnPoint),
	Entity(id, spawnPoint->getX(), spawnPoint->getY()),
	DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
	CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 8, 20, 16, 12),
	MovableEntity(id, spawnPoint->getX(), spawnPoint->getY())
{
	this->setWidth(32);
	this->setHeight(32);

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

	this->keepAnimationWhenIdle = true;
	this->firstImgID = firstImgID;
	this->animationWalkUpRow = 0, this->animationWalkLeftRow = 1;
	this->animationWalkDownRow = 2, this->animationWalkRightRow = 3;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; this->animationWalkStartColumn = 0, this->animationWalkEndColumn = 3;
	//this->playerAnimationActionStartColumn = 1; this->playerAnimationActionEndColumn = 5;
	this->frameAmountX = 4, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;//, this->animationDelay = 1;

	this->timeSinceLastAction = 0;

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);

	this->StopAnimation();
}

void Wasp::update(double dt) 
{
}

void Wasp::changeState(State* pNewState)
{
	assert(getCurrentState() && pNewState);
	this->getCurrentState()->Exit(this);
	this->setCurrentState(pNewState);
	this->getCurrentState()->Enter(this);
}

void Wasp::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Wasp::ResetDrawableEntityAndSetChunk()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	this->setChunks(); 
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
}

bool Wasp::checkCollision(double newX, double newY)
{
	return CollidableEntity::checkCollision(newX, newY);
}

Wasp::~Wasp()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
}