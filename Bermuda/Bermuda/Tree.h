#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "InteractableEntity.h"
#include "Items.h"

class Tree :
	public DrawableEntity, public CollidableEntity, public InteractableEntity
{
private:
	Image* treeImage;
	Image* stumpImage;
public:
	Tree(int id, double x, double y, Image* treeImage, Image* stumpImage);
	void update(double dt);
	void respawn();
	void interact(Player* player);
	void setDestroyedState();
	~Tree();
};
