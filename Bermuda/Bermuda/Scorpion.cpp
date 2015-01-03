#include "Scorpion.h"
#include "PlayState.h"
#include <time.h>
#include <iostream>
#include <random>
#include "WanderAround.h"
#include "AggressiveState.h"


Scorpion::Scorpion(int id, Spawnpoint* spawnPoint, int firstImgID) :
	NPC(id, 5, 1, 50, spawnPoint),
	Entity(id, spawnPoint->getX(), spawnPoint->getY()),
	DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
	CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 2, 8, 28, 21),
	MovableEntity(id, spawnPoint->getX(), spawnPoint->getY())
{
	this->setWidth(48);
	this->setHeight(48);
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

	//this->keepAnimationWhenIdle = true;
	this->firstImgID = firstImgID;
	this->animationWalkUpRow = 1; 
	this->animationWalkLeftRow = 2;
	this->animationWalkDownRow = 0, 
	this->animationWalkRightRow = 3;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; 
	this->animationWalkStartColumn = 0;
	this->animationWalkEndColumn = 3;
	//this->playerAnimationActionStartColumn = 1; this->playerAnimationActionEndColumn = 5;
	this->frameAmountX = 6, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;//, this->animationDelay = 1;

	this->timeSinceLastAction = 0;

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);

	this->StopAnimation();

	//this->m_pStateMachine = new StateMachine<Entity>(this);
	//this->m_pStateMachine->setCurrentState(WanderAround::Instance());
	//this->m_pStateMachine->setGlobalState(WanderAround::Instance());
}

void Scorpion::update(double dt)
{
	double diffX = PlayState::Instance()->getPlayer()->getCenterX() - this->getCenterX();
	double diffY = PlayState::Instance()->getPlayer()->getCenterY() - this->getCenterY();
	double distanceFromPlayer = sqrt((diffX * diffX) + (diffY * diffY));

	// TODO: look for a good way to stop the movement
	//if (this->m_pStateMachine->getCurrentState() == AggressiveState::Instance() && distanceFromPlayer < 5)
	//{
	//	std::cout << "Scorpion is now attacking \n";
	//}
	//else
	//{
	//	if (this->m_pStateMachine->getCurrentState() == WanderAround::Instance() && distanceFromPlayer <= 150)
	//	{
	//		this->m_pStateMachine->changeState(AggressiveState::Instance());
	//	}
	//	else if (this->m_pStateMachine->getCurrentState() == AggressiveState::Instance() && distanceFromPlayer >= 300)
	//	{
	//		this->m_pStateMachine->changeState(WanderAround::Instance());
	//	}

	//	this->m_pStateMachine->update(dt);
	//}
}

void Scorpion::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Scorpion::ResetDrawableEntityAndSetChunk()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	this->setChunks(); 
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
}

bool Scorpion::checkCollision(double newX, double newY)
{
	return CollidableEntity::checkCollision(newX, newY);
}

Scorpion::~Scorpion()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
}
