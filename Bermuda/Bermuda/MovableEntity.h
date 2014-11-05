#pragma once
#include "entity.h"

class MovableEntity :
	virtual public Entity
{

public:
	MovableEntity(int id, double x, double y, int chunkSize, double moveSpeed);
	//Speed Variables
	double stopSpeed;
	double minSpeed;
	double moveSpeed;
	double maxSpeed;
	double sprintSpeed;
	bool sprinting;
	//Direction Booleans
	bool movingLeft;
	bool movingRight;
	bool movingDown;
	bool movingUp;
	//Direction Variables
	double dx;
	double dy;
	virtual void move(double dt) = 0;
	virtual ~MovableEntity(void);
};

