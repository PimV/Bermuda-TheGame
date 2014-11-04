#pragma once
#include "Entity.h"
class MovableEntity :
	virtual public Entity
{
public:
	MovableEntity(int id, double x, double y, int chunkSize);
	virtual ~MovableEntity();

	void setMoveSpeed(double moveSpeed);
	double getMoveSpeed();



private:
	double moveSpeed;
};

