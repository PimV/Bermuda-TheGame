#include "Carrot.h"


Carrot::Carrot(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* carrotImage)
	: Entity(id,x,y,chunkSize), DrawableEntity(id,x,y,chunkSize, carrotImage)
{
	mec->getDrawableContainer()->add(this);
}


Carrot::~Carrot()
{
}
