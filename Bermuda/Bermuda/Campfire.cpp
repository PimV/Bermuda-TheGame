#include "Campfire.h"
#include "PlayState.h"
#include "ParticleTypes.h"


Campfire::Campfire(int id, double x, double y, int firstImgID) :
	Entity(id, x, y),
	AnimatingEntity(id, x, y, firstImgID),
	CollidableEntity(id, x, y, 0, 31, 50, 21)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getAnimatingContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	this->creationTime = GameTimer::Instance()->getGameTime();
	this->lifeTime = GameTimer::Instance()->getNightLength() + 40000;
	this->setAnimation(1, 3, 100, GameTimer::Instance()->getNightLength() + 20000, 0);

	this->particleEngine = new ParticleEngine(0,x + 10,y + 40,nullptr,PARTICLETYPES::SMOKE);
}

void Campfire::animate(double dt)
{
	this->particleEngine->updateParticles(dt);

	AnimatingEntity::animate(dt);
	long currentTime = GameTimer::Instance()->getGameTime();
	if (this->creationTime + lifeTime < currentTime)
	{
		PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
		delete this->particleEngine;
	}
}

Campfire::~Campfire()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getAnimatingContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
