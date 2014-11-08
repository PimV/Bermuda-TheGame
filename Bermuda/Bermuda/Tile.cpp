#include "Tile.h"


Tile::Tile(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* image)
	: Entity(id,x,y,chunkSize),
	DrawableEntity(id,x,y,chunkSize, image)
{
	this->setMainEntityContainer(mec);
	this->getMainEntityContainer()->getBackgroundContainer()->add(this);
	//mec->getBackgroundContainer()->add(this);
}


Tile::~Tile()
{
	//TODO: Remove object from his containers here?
	this->getMainEntityContainer()->getBackgroundContainer()->remove(this);
}
