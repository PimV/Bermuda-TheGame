#pragma once
class Collidable
{
public:
	Collidable(double collisionX, double collisionY, double collisionWidth, double collisionHeight);
	Collidable();

	void setCollisionX(double x);
	void setCollisionY(double y);
	void setCollisionWidth(double width);
	void setCollisionHeight(double height);

	double mapX;
	double mapY;
	double mapWidth;
	double mapHeight;


	double getCollisionX();
	double getCollisionY();
	double getCollisionWidth();
	double getCollisionHeight();

	bool intersects(Collidable* collidable);

	virtual ~Collidable();

private: 	


	double collisionX;
	double collisionY;
	double collisionWidth;
	double collisionHeight;

};