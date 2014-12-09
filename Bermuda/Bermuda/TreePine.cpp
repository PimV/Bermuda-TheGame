#include "TreePine.h"
#include "PlayState.h"
#include "Overlays.h"


TreePine::TreePine(int id, double x, double y, Image* treeImage, Image* stumpImage) :
	Entity(id,x,y),
	Tree(id, x, y, treeImage, stumpImage)
{
	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::treePine));
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::treePineCant));

	this->setHighlightTexture(this->getCantInteractTexture());
}

TreePine::~TreePine()
{
}
