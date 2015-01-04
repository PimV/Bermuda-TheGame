#include "Wolf.h"
#include "PlayState.h"
#include <time.h>
#include <iostream>
#include <random>
#include "AggressiveBehaviour.h"

Wolf::Wolf(int id, Spawnpoint* spawnPoint, int firstImgID) :
	NPC(id, 5, 3, 150, 5, spawnPoint),
	Entity(id, spawnPoint->getX(), spawnPoint->getY()),
	DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
	CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 13, 20, 23, 24),
	MovableEntity(id, spawnPoint->getX(), spawnPoint->getY()),
	AttackingNPC(500)
{
	this->setWidth(48);
	this->setHeight(48);

	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 3;
	this->moveSpeed = 2;
	this->stopSpeed = 0.8;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;

	this->firstImgID = firstImgID;
	this->animationWalkUpRow = 3; 
	this->animationWalkLeftRow = 1;
	this->animationWalkDownRow = 0, 
	this->animationWalkRightRow = 2;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; 
	this->animationWalkStartColumn = 0;
	this->animationWalkEndColumn = 3;
	this->frameAmountX = 4, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;

	this->timeSinceLastAction = 0;

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);

	this->StopAnimation();

	this->behaviour = new AggressiveBehaviour( new StateMachine<Entity>(this) );
}

void Wolf::update(double dt)
{
	this->behaviour->update(dt);
}

void Wolf::attack()
{
	if( this->checkAttackTimes())
	{
		PlayState::Instance()->getPlayer()->setHealth( ( PlayState::Instance()->getPlayer()->getHealth() - this->getAttackPoints() ) );
	}
}

void Wolf::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Wolf::ResetDrawableEntityAndSetChunk()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	this->setChunks(); 
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
}

bool Wolf::checkCollision(double newX, double newY)
{
	return CollidableEntity::checkCollision(newX, newY);
}

Wolf::~Wolf()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
}
