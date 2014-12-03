#include "RuinStatue.h"
#include "PlayState.h"

RuinStatue::RuinStatue(int id, double x, double y, Image* image) :
	Entity(id,x,y), 
	DrawableEntity(id, x, y, image), 
	CollidableEntity(id, x, y, 0, 32, 32, 32)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
}


RuinStatue::~RuinStatue()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
