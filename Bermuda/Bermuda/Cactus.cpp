#include "Cactus.h"

Cactus::Cactus(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* image) :
	Entity(id, x, y, chunkSize),
	DrawableEntity(id, x, y, chunkSize, image),
	CollidableEntity(id, x, y, chunkSize, 18, 76, 28, 15)
{
	this->setMainEntityContainer(mec);
	this->getMainEntityContainer()->getDrawableContainer()->add(this);
	this->getMainEntityContainer()->getCollidableContainer()->add(this);
}


Cactus::~Cactus()
{
	this->getMainEntityContainer()->getDrawableContainer()->remove(this);
	this->getMainEntityContainer()->getCollidableContainer()->remove(this);
}
