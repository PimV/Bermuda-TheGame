#pragma once
#include "EnumDirection.h"
class IMovable
{
public:
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

	IMovable(double mSpeed) : moveSpeed(mSpeed){};
	virtual ~IMovable(void);

	virtual void move(double dt) = 0;

	// move method
	// speed
};

