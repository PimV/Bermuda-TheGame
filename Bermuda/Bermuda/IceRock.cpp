#include "IceRock.h"
#include "PlayState.h"


IceRock::IceRock(int id, double x, double y, Image* rockImage, Image* rockPieces) :
	Entity(id,x,y),
	Ice(id, x, y, rockImage, rockPieces)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getInteractRockImage());
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getCantInteractRockImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}


IceRock::~IceRock()
{
}
