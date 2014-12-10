#include "InteractableCactusSmall.h"
#include "PlayState.h"
#include "Overlays.h"


InteractableCactusSmall::InteractableCactusSmall(int id, double x, double y, Image* cactusImage, Image* stumpImage) :
	Entity(id,x,y),
	InteractableCactus(id, x, y, cactusImage, stumpImage)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::cactusSmall));
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::cactusSmallCant));

	this->setHighlightTexture(this->getCantInteractTexture());
}


InteractableCactusSmall::~InteractableCactusSmall()
{
}
