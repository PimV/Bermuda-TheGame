#include "TreeRound.h"
#include "GameStateManager.h"


TreeRound::TreeRound(int id, double x, double y, Image* treeImage, Image* stumpImage) :
	Entity(id,x,y),
	Tree(id, x, y, treeImage, stumpImage)
{
	this->setCanInteractTexture(GameStateManager::Instance()->getImageLoader()->getInteractTreeImage());
	this->setCantInteractTexture(GameStateManager::Instance()->getImageLoader()->getCantInteractTreeImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}


TreeRound::~TreeRound()
{
}
