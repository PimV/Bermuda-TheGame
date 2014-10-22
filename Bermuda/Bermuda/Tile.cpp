#include "Tile.h"


Tile::Tile(int id, int x, int y, int chunkSize, MainEntityContainer* mec, Image* image)
	: Entity(id,x,y,chunkSize), DrawableEntity(id,x,y,chunkSize, image)
{
	mec->getBackgroundContainer()->add(this);
}


Tile::~Tile()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
