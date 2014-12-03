#pragma once
#include "AnimatingEntity.h"
#include "CollidableEntity.h"
#include "InteractableEntity.h"

class Campfire :
	public AnimatingEntity, public CollidableEntity
{
private:
	double creationTime;
	double lifeTime;
public:
	Campfire(int id, double x, double y, int firstImgID);
	static void animationStopped();
	void animate();
	virtual ~Campfire();
};

