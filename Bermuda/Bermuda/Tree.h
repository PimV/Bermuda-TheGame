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
	Tree(int id, double x, double y, int chunkSize, MainEntityContainer* mec, Image* treeImage, Image* stumpImage);
	void setCollidableValues();
	~Tree();
};

