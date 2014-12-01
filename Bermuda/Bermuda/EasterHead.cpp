#include "EasterHead.h"
#include "PlayState.h"

EasterHead::EasterHead(int id, double x, double y, Image* image) :
	Entity(id, x, y),
	DrawableEntity(id, x, y, image),
	CollidableEntity(id, x, y, 4, 68, 52, 21)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
}


EasterHead::~EasterHead()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
