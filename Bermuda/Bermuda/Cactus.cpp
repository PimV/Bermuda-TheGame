#include "Cactus.h"
#include "PlayState.h"

Cactus::Cactus(int id, double x, double y, Image* image) :
	Entity(id, x, y),
	DrawableEntity(id, x, y, image),
	CollidableEntity(id, x, y, 18, 76, 28, 15)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
}


Cactus::~Cactus()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
