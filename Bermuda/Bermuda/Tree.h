#pragma once
#include "DrawableEntity.h"
#include "Collidable.h"
#include "MainEntityContainer.h"

class Tree :
	public DrawableEntity, public Collidable
{
private:
	Image* treeImage;
	Image* stumpImage;
	MainEntityContainer* mec;
public:
	Tree(int id, MainEntityContainer* mec,  double x, double y, Image* treeImage, Image* stumpImage);
	void setCollidableValues();
	~Tree();
};

