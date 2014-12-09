#include "IceRock.h"
#include "PlayState.h"
#include "Overlays.h"


IceRock::IceRock(int id, double x, double y, Image* rockImage, Image* rockPieces) :
	Entity(id,x,y),
	Ice(id, x, y, rockImage, rockPieces)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::rock));
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::rockCant));

	this->setHighlightTexture(this->getCantInteractTexture());
}


IceRock::~IceRock()
{
}
