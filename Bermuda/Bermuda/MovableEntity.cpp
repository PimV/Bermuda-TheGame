#include "MovableEntity.h"

MovableEntity::MovableEntity(int id, double x, double y, int chunkSize) : 
Entity(id, x, y, chunkSize)
{
}

#pragma region Setters
void MovableEntity::setMoveSpeed(double moveSpeed)
{
	this->moveSpeed = moveSpeed;
}
#pragma endregion


#pragma region Getters
double MovableEntity::getMoveSpeed()
{
	return this->moveSpeed;
}
#pragma endregion


MovableEntity::~MovableEntity()
{
}
