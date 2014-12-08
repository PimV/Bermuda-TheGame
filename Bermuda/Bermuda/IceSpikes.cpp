#include "IceSpikes.h"
#include "PlayState.h"


IceSpikes::IceSpikes(int id, double x, double y, Image* rockImage, Image* rockPieces) :
	Entity(id,x,y),
	Ice(id, x, y, rockImage, rockPieces)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getInteractSpikeImage());
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getCantInteractSpikeImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}


IceSpikes::~IceSpikes()
{
}
