#include "Tree.h"

Tree::Tree(int id, int x, int y, int chunkSize, MainEntityContainer* mec, Image* treeImage, Image* stumpImage)
	: Entity(id,x,y,chunkSize), DrawableEntity(id,x,y,chunkSize, treeImage), CollidableEntity(id,x,y,chunkSize, 34, 102, 27, 15), mec(mec), treeImage(treeImage), stumpImage(stumpImage)
{
	mec->getDrawableContainer()->add(this);
	mec->getCollidableContainer()->add(this);
}

//TODO: Use this->setDrawImage() to change to stump or tree. 

Tree::~Tree()
{
	//TODO: Remove object from his containers here?
	//mec->getDrawableContainer()->remove(this);
}
