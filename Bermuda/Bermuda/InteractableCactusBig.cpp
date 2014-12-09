#include "InteractableCactusBig.h"
#include "PlayState.h"
#include "Overlays.h"


InteractableCactusBig::InteractableCactusBig(int id, double x, double y, Image* cactusImage, Image* stumpImage) :
	Entity(id,x,y),
	InteractableCactus(id, x, y, cactusImage, stumpImage)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::cactusBig));
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::cactusBigCant));

	this->setHighlightTexture(this->getCantInteractTexture());
}

InteractableCactusBig::~InteractableCactusBig()
{
}
