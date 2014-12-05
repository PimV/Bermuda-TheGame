#include "IceRock.h"
#include "GameStateManager.h"


IceRock::IceRock(int id, double x, double y, Image* rockImage, Image* rockPieces) :
	Entity(id,x,y),
	Ice(id, x, y, rockImage, rockPieces)
{
	this->setCanInteractTexture(GameStateManager::Instance()->getImageLoader()->getInteractRockImage());
	this->setCantInteractTexture(GameStateManager::Instance()->getImageLoader()->getCantInteractRockImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}


IceRock::~IceRock()
{
}
