#include "Pillar.h"
#include "PlayState.h"

Pillar::Pillar(int id, double x, double y, Image* image) :
	Entity(id,x,y), 
	DrawableEntity(id, x, y, image), 
	CollidableEntity(id, x, y, 0, 64, 32, 32)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
}


Pillar::~Pillar()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
