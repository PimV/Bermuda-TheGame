#pragma once
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "InteractableEntity.h"

class AppleTree :
	public DrawableEntity, public CollidableEntity, public InteractableEntity
{
private:
	Image* treeImage;
	Image* treeEmptyImage;
	Image* stumpImage;
public:
	AppleTree(int id, double x, double y, Image* treeImage, Image* treeEmptyImage, Image* stumpImage);
	void setCollidableValues();
	void update(double dt);
	void respawn();
	void interact(Player* player);
	void setDestroyedState();
	virtual ~AppleTree();
};

