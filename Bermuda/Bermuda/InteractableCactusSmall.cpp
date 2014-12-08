#include "InteractableCactusSmall.h"
#include "PlayState.h"


InteractableCactusSmall::InteractableCactusSmall(int id, double x, double y, Image* cactusImage, Image* stumpImage) :
	Entity(id,x,y),
	InteractableCactus(id, x, y, cactusImage, stumpImage)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getInteractCactusSmallImage());
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getCantInteractCactusSmallImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}


InteractableCactusSmall::~InteractableCactusSmall()
{
}
