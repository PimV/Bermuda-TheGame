#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "MainEntityContainer.h"

class Tree :
	public DrawableEntity, public CollidableEntity
{
private:
	Image* treeImage;
	Image* stumpImage;
	MainEntityContainer* mec;
public:
	Tree(int id, int chunkSize, MainEntityContainer* mec,  double x, double y, Image* treeImage, Image* stumpImage);
	void setCollidableValues();
	~Tree();
};

