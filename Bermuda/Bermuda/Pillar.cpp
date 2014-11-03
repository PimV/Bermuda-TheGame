#include "Pillar.h"

Pillar::Pillar(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* image) :
	Entity(id,x,y,chunkSize), 
	DrawableEntity(id, x, y, chunkSize, image), 
	CollidableEntity(id, x, y, chunkSize, 0, 64, 32, 32)
{
	this->setMainEntityContainer(mec);
	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	this->getMainEntityContainer()->getCollidableContainer()->add(this);
}


Pillar::~Pillar()
{
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	this->getMainEntityContainer()->getCollidableContainer()->remove(this);
}