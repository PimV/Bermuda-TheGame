#include "Scorpion.h"
#include "PlayState.h"
#include <time.h>
#include <iostream>
#include <random>
#include "AggressiveBehaviour.h"

Scorpion::Scorpion(int id, Spawnpoint* spawnPoint, int firstImgID) :
	InteractableNPC(id, 5, 1, 150, 5, spawnPoint, -18, -15, 68, 78),
	Entity(id, spawnPoint->getX(), spawnPoint->getY()),
	DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
	CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 2, 8, 28, 21),
	MovableEntity(id, spawnPoint->getX(), spawnPoint->getY()),
	AttackingNPC(500)
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

	this->firstImgID = firstImgID;
	this->animationWalkUpRow = 1; 
	this->animationWalkLeftRow = 2;
	this->animationWalkDownRow = 0, 
	this->animationWalkRightRow = 3;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; 
	this->animationWalkStartColumn = 0;
	this->animationWalkEndColumn = 3;
	this->frameAmountX = 6, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;

	this->timeSinceLastAction = 0;

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);

	this->StopAnimation();

	this->behaviour = new AggressiveBehaviour( new StateMachine<Entity>(this) );
}

void Scorpion::update(double dt)
{
	this->behaviour->update(dt);
}

void Scorpion::attack()
{
	if( this->checkAttackTimes())
	{
		PlayState::Instance()->getPlayer()->setHealth( ( PlayState::Instance()->getPlayer()->getHealth() - this->getAttackPoints() ) );
	}
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
