#include "Campfire.h"
#include "PlayState.h"
#include "ParticleTypes.h"


Campfire::Campfire(int id, double x, double y, int firstImgID) :
	Entity(id, x, y),
	AnimatingEntity(id, x, y, firstImgID),
	CollidableEntity(id, x, y, 0, 31, 50, 21),
	LightEntity(id, x, y)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getAnimatingContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getLightContainer()->add(this);
	this->creationTime = GameTimer::Instance()->getGameTime();
	startAnimationTimerType(1, 3, 100, GameTimer::Instance()->getNightLength() + 10000, 0);
	this->particleEngine = new ParticleEngine(0,x + 10,y + 40,nullptr,PARTICLETYPES::SMOKE);
}

void Campfire::animate(double dt)
{
	AnimatingEntity::animate(dt);
	this->particleEngine->updateParticles(dt);

	long currentTime = GameTimer::Instance()->getGameTime();
	if (this->destroyTime > 0 && this->destroyTime < currentTime)
	{
		PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
		delete this->particleEngine;
	}
}

void Campfire::animationFinished()
{
	this->destroyTime = GameTimer::Instance()->getGameTime() + 20000;
}

Campfire::~Campfire()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getAnimatingContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getLightContainer()->remove(this);
}
