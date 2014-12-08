#include "TreePine.h"
#include "PlayState.h"


TreePine::TreePine(int id, double x, double y, Image* treeImage, Image* stumpImage) :
	Entity(id,x,y),
	Tree(id, x, y, treeImage, stumpImage)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getInteractTreePineImage());
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getCantInteractTreePineImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}

TreePine::~TreePine()
{
}
