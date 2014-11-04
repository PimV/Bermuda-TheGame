#pragma once
#include "entity.h"

class CollidableEntity :
	public virtual Entity
{
private: 
	double collisionX;
	double collisionY;
	double collisionWidth;
	double collisionHeight;
public:
	CollidableEntity(int id, double x, double y, int chunkSize, double collisionX, double collisionY, double collisionWidth, double collisionHeight);
	CollidableEntity(int id, double x, double y, int chunkSize);
	CollidableEntity();

	void setCollisionX(double x);
	void setCollisionY(double y);
	void setCollisionWidth(double width);
	void setCollisionHeight(double height);

	double getCollisionX();
	double getCollisionY();
	double getCollisionWidth();
	double getCollisionHeight();

	bool intersects(CollidableEntity* collidableEntity);

	virtual ~CollidableEntity();
};