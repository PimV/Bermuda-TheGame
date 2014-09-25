#pragma once
class IMovable
{
public:
	//Speed Variables
	double minSpeed;
	double moveSpeed;
	double maxSpeed;
	//Direction Booleans
	bool movingLeft;
	bool movingRight;
	bool movingDown;
	bool movingUp;
	//Direction Variables
	double dx;
	double dy;

	virtual void move() = 0;
	virtual ~IMovable(void);

};

