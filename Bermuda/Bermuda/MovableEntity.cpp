#include "MovableEntity.h"


MovableEntity::MovableEntity(int id, double x, double y, int chunkSize, double moveSpeed)
	: Entity(id,x,y,chunkSize)
{
	this->moveSpeed = moveSpeed;
}


MovableEntity::~MovableEntity(void)
{
}
