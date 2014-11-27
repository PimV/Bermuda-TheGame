#include "Campfire.h"
#include "PlayState.h"


Campfire::Campfire(int id, double x, double y, int chunkSize, int firstImgID) :
	Entity(id, x, y, chunkSize),
	AnimatingEntity(id, x, y, chunkSize, firstImgID),
	CollidableEntity(id, x, y, chunkSize, 0, 31, 50, 21)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getAnimatingContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	this->creationTime = GameTimer::Instance()->getGameTime();
	this->lifeTime = 6000;
	setAnimation(1, 3, 100, 3000, 0);
}

void Campfire::animate()
{
	AnimatingEntity::animate();
	long currentTime = GameTimer::Instance()->getGameTime();
	if (this->creationTime + lifeTime < currentTime)
	{
		PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
	}
}

Campfire::~Campfire()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getAnimatingContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
