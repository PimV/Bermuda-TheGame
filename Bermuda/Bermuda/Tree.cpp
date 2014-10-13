#include "Tree.h"

/*
Tree::Tree(int id, Image* treeImage, Image* stumpImage)
	: DrawableEntity(id, treeImage), treeImage(treeImage), stumpImage(stumpImage)
{
}*/

Tree::Tree(int id, Image* treeImage)
	: DrawableEntity(id, treeImage), treeImage(treeImage)
{
}

//TODO: Use this->setDrawImage() to change to stump or tree. 

Tree::~Tree()
{
}
