#pragma once
#include "DrawableEntity.h"
class Tree :
	public DrawableEntity
{
private:
	Image* treeImage;
	Image* stumpImage;
public:
	//Tree(int id, Image* treeImage, Image* stumpImage);
	Tree(int id, Image* treeImage);
	~Tree();
};

