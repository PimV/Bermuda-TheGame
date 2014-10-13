#include "Tile.h"


Tile::Tile(int id, MainEntityContainer* mec, double x, double y, Image* image)
	: DrawableEntity(id, image)
{
	setX(x);
	setY(y);
	mec->getDrawableContainer()->add(this);
}


Tile::~Tile()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
