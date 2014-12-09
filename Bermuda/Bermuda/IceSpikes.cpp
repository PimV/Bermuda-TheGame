#include "IceSpikes.h"
#include "PlayState.h"
#include "Overlays.h"


IceSpikes::IceSpikes(int id, double x, double y, Image* rockImage, Image* rockPieces) :
	Entity(id,x,y),
	Ice(id, x, y, rockImage, rockPieces)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::spike));
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::spikeCant));

	this->setHighlightTexture(this->getCantInteractTexture());
}


IceSpikes::~IceSpikes()
{
}
