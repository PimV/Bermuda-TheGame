#include "Tile.h"


Tile::Tile(int id, int chunkSize, MainEntityContainer* mec, double x, double y, Image* image)
	: Entity(id), DrawableEntity(id, image)
{
	setX(x);
	setY(y);
	setChunkSize(chunkSize);
	//mec->getDrawableContainer()->add(this);
	mec->getBackgroundContainer()->add(this);
}


Tile::~Tile()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
