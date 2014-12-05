#include "TreePine.h"
#include "GameStateManager.h"


TreePine::TreePine(int id, double x, double y, Image* treeImage, Image* stumpImage) :
	Entity(id,x,y),
	Tree(id, x, y, treeImage, stumpImage)
{
	this->setCanInteractTexture(GameStateManager::Instance()->getImageLoader()->getInteractTreePineImage());
	this->setCantInteractTexture(GameStateManager::Instance()->getImageLoader()->getCantInteractTreePineImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}

TreePine::~TreePine()
{
}
