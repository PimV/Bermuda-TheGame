#include "TreeRound.h"
#include "PlayState.h"


TreeRound::TreeRound(int id, double x, double y, Image* treeImage, Image* stumpImage) :
	Entity(id,x,y),
	Tree(id, x, y, treeImage, stumpImage)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getInteractTreeImage());
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getCantInteractTreeImage());

	this->setHighlightTexture(this->getCantInteractTexture());
}


TreeRound::~TreeRound()
{
}