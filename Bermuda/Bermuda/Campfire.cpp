#include "Campfire.h"
#include "PlayState.h"


Campfire::Campfire(int id, double x, double y, int chunkSize, Image* image) :
	Entity(id, x, y, chunkSize),
	DrawableEntity(id, x, y, chunkSize, image),
	CollidableEntity(id, x, y, chunkSize, 0, 31, 50, 21)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
}

Campfire::~Campfire()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
