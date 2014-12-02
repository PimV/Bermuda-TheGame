#pragma once
#include "AnimatingEntity.h"
#include "CollidableEntity.h"
#include "InteractableEntity.h"
#include "LightEntity.h"

class Campfire :
	public AnimatingEntity, public CollidableEntity, public LightEntity
{
private:
	double creationTime;
	double lifeTime;
public:
	Campfire(int id, double x, double y, int firstImgID);
	void animate();
	virtual ~Campfire();
};

