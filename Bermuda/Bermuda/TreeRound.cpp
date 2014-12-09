#include "TreeRound.h"
#include "PlayState.h"
#include "Overlays.h"


TreeRound::TreeRound(int id, double x, double y, Image* treeImage, Image* stumpImage) :
	Entity(id,x,y),
	Tree(id, x, y, treeImage, stumpImage)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::treeRound));
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::treeRoundCant));

	this->setHighlightTexture(this->getCantInteractTexture());
}


TreeRound::~TreeRound()
{
}