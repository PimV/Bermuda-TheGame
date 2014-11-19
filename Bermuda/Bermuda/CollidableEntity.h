#pragma once
#include "entity.h"
#include "header_loader.h"

class MovableEntity;

class CollidableEntity :
	virtual public Entity
{
private: 
	double collisionX;
	double collisionY;
	double collisionWidth;
	double collisionHeight;
	
	SDL_Rect collidableRect;
	SDL_Texture* collidableTexture;
public:
	CollidableEntity(int id, double x, double y, int chunkSize, double collisionX, double collisionY, double collisionWidth, double collisionHeight);
	CollidableEntity(int id, double x, double y, int chunkSize);
	CollidableEntity();

	void setCollisionX(double x);
	void setCollisionY(double y);
	void setCollisionWidth(double width);
	void setCollisionHeight(double height);

	void drawCollidableArea();

	double getCollisionX();
	double getCollisionY();
	double getCollisionWidth();
	double getCollisionHeight();

	bool intersects(CollidableEntity* collidableEntity, MovableEntity* movableEntity);

	virtual ~CollidableEntity();
};