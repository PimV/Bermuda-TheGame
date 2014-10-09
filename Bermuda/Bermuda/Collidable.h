#pragma once
class Collidable
{
public:
	Collidable(double collisionX, double collisionY, double collisionWidth, double collisionHeight);

	void setCollisionX(double x);
	void setCollisionY(double y);
	void setCollisionWidth(double width);
	void setCollisionHeight(double height);

	double getCollisionX();
	double getCollisionY();
	double getCollisionWidth();
	double getCollisionHeight();

	virtual ~Collidable();

private: 	
	//Entity Position
	double collisionX;
	double collisionY;
	//Entity Size
	double collisionWidth;
	double collisionHeight;

};

