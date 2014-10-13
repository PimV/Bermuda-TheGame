#include "Tree.h"

Tree::Tree(int id, MainEntityContainer* mec, double x, double y, Image* treeImage, Image* stumpImage)
	: Entity(id), DrawableEntity(id, treeImage), CollidableEntity(id, 34, 102, 27, 15), mec(mec), treeImage(treeImage), stumpImage(stumpImage)
{
	setX(x);
	setY(y);
	mec->getDrawableContainer()->add(this);
	mec->getCollidableContainer()->add(this);
}

//TODO: Use this->setDrawImage() to change to stump or tree. 

Tree::~Tree()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
