#include "RockSpikes.h"
#include "PlayState.h"


RockSpikes::RockSpikes(int id, double x, double y, Image* image) :
	Entity(id, x, y),
	DrawableEntity(id, x, y, image),
	CollidableEntity(id, x, y, 0, 14, 32, 18)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
}


RockSpikes::~RockSpikes()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
