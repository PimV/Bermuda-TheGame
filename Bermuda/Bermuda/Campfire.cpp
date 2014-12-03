#include "Campfire.h"
#include "PlayState.h"


Campfire::Campfire(int id, double x, double y, int firstImgID) :
	Entity(id, x, y),
	AnimatingEntity(id, x, y, firstImgID),
	CollidableEntity(id, x, y, 0, 31, 50, 21)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getAnimatingContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	this->creationTime = GameTimer::Instance()->getGameTime();
	//this->lifeTime = GameTimer::Instance()->getNightLength() + 40000;
	//this->setAnimation(1, 3, 100, GameTimer::Instance()->getNightLength() + 20000, 0);

	// remove when particle are being show
	this->lifeTime = GameTimer::Instance()->getNightLength() + 60000;
	this->setAnimation(1, 3, 100, GameTimer::Instance()->getNightLength() + 40000, 0);
}

void Campfire::animate()
{
	AnimatingEntity::animate();
	long currentTime = GameTimer::Instance()->getGameTime();
	if (this->creationTime + lifeTime < currentTime)
	{
		PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
		PlayState::Instance()->getMainEntityContainer()->getParticleContainer()->removeEffect(this->pe);
		delete this->pe;
	}
}

void Campfire::setParticleEngine(ParticleEngine* _pe)
{
	this->pe = _pe;
	PlayState::Instance()->getMainEntityContainer()->getParticleContainer()->addEffect(this->pe);
}

Campfire::~Campfire()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getAnimatingContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
