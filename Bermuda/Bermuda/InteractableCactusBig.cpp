#include "InteractableCactusBig.h"
#include "GameStateManager.h"


InteractableCactusBig::InteractableCactusBig(int id, double x, double y, Image* cactusImage, Image* stumpImage) :
	Entity(id,x,y),
	InteractableCactus(id, x, y, cactusImage, stumpImage)
{
	this->setCanInteractTexture(GameStateManager::Instance()->getImageLoader()->getInteractCactusBigImage());
	this->setCantInteractTexture(GameStateManager::Instance()->getImageLoader()->getCantInteractCactusBigImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}

InteractableCactusBig::~InteractableCactusBig()
{
}
