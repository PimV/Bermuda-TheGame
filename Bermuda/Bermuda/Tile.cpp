#include "Tile.h"
#include "PlayState.h"

Tile::Tile(int id, double x, double y, Image* image) : 
	Entity(id,x,y), 
	DrawableEntity(id,x,y, image)
{
	PlayState::Instance()->getMainEntityContainer()->getBackgroundContainer()->add(this);
}

Tile::~Tile()
{
	PlayState::Instance()->getMainEntityContainer()->getBackgroundContainer()->remove(this);
}
