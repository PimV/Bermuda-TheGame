#include "SnowTree.h"
#include "PlayState.h"


SnowTree::SnowTree(int id, double x, double y, Image* image) :
	Entity(id,x,y), 
	DrawableEntity(id,x,y, image), 
	CollidableEntity(id,x,y, 34, 102, 27, 15)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
}


SnowTree::~SnowTree()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
