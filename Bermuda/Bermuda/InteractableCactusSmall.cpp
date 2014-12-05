#include "InteractableCactusSmall.h"
#include "GameStateManager.h"


InteractableCactusSmall::InteractableCactusSmall(int id, double x, double y, Image* cactusImage, Image* stumpImage) :
	Entity(id,x,y),
	InteractableCactus(id, x, y, cactusImage, stumpImage)
{
	this->setCanInteractTexture(GameStateManager::Instance()->getImageLoader()->getInteractCactusSmallImage());
	this->setCantInteractTexture(GameStateManager::Instance()->getImageLoader()->getCantInteractCactusSmallImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}


InteractableCactusSmall::~InteractableCactusSmall()
{
}
