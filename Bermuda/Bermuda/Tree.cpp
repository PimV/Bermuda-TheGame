#include "Tree.h"

Tree::Tree(int id, MainEntityContainer* mec, double x, double y, Image* treeImage, Image* stumpImage)
	: DrawableEntity(id, treeImage), Collidable(34, 102, 27, 15), mec(mec), treeImage(treeImage), stumpImage(stumpImage)
{
	setX(x);
	setY(y);
	setCollidableValues();
	mec->getDrawableContainer()->add(this);
	mec->getCollidableContainer()->add(this);
}

void Tree::setCollidableValues()
{
	this->mapX = this->getX();
	this->mapY = this->getY();
	this->mapWidth = this->getWidth();
	this->mapHeight = this->getHeight();
}

//TODO: Use this->setDrawImage() to change to stump or tree. 

Tree::~Tree()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
