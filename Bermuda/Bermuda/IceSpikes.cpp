#include "IceSpikes.h"
#include "GameStateManager.h"


IceSpikes::IceSpikes(int id, double x, double y, Image* rockImage, Image* rockPieces) :
	Entity(id,x,y),
	Ice(id, x, y, rockImage, rockPieces)
{
	this->setCanInteractTexture(GameStateManager::Instance()->getImageLoader()->getInteractSpikeImage());
	this->setCantInteractTexture(GameStateManager::Instance()->getImageLoader()->getCantInteractSpikeImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}


IceSpikes::~IceSpikes()
{
}
