#include "InteractableCactusBig.h"
#include "PlayState.h"


InteractableCactusBig::InteractableCactusBig(int id, double x, double y, Image* cactusImage, Image* stumpImage) :
	Entity(id,x,y),
	InteractableCactus(id, x, y, cactusImage, stumpImage)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getInteractCactusBigImage());
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getCantInteractCactusBigImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}

InteractableCactusBig::~InteractableCactusBig()
{
}
