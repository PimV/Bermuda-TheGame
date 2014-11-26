#pragma once
#include "AnimatingEntity.h"
#include "CollidableEntity.h"

class Campfire :
	public AnimatingEntity, public CollidableEntity
{
private:
	double creationTime;
	double lifeTime;
public:
	Campfire(int id, double x, double y, int chunkSize, int firstImgID);
	void animate(double dt);
	virtual ~Campfire();
};

