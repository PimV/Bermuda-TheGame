#include "Bat.h"
#include "PlayState.h"
#include <random>
#include "EvasiveBehaviour.h"

Bat::Bat(int id, Spawnpoint* spawnPoint, int firstImgID) :
NPC(id, 5, 1, 50, 15, spawnPoint),
Entity(id, spawnPoint->getX(), spawnPoint->getY()),
DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 8, 20, 16, 12),
MovableEntity(id, spawnPoint->getX(), spawnPoint->getY()),
AttackingNPC(500)
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
	this->frameAmountX = 4, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;

	this->timeSinceLastAction = 0;

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);

	this->StopAnimation();

	this->behaviour = new EvasiveBehaviour( new StateMachine<Entity>(this) );
}

void Bat::update(double dt)
{
	this->behaviour->update(dt);
}

void Bat::attack()
{
	if( this->checkAttackTimes())
	{
		PlayState::Instance()->getPlayer()->setHealth( ( PlayState::Instance()->getPlayer()->getHealth() - this->getAttackPoints() ) );
	}
}

void Bat::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Bat::ResetDrawableEntityAndSetChunk()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	this->setChunks();
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
}

bool Bat::checkCollision(double newX, double newY)
{
	return CollidableEntity::checkCollision(newX, newY);
}

Bat::~Bat()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
}
