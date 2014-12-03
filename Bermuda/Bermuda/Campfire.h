#pragma once
#include "AnimatingEntity.h"
#include "CollidableEntity.h"
#include "InteractableEntity.h"

class Campfire :
	public AnimatingEntity, public CollidableEntity
{
private:
	double creationTime;
	double destroyTime;
protected:
	virtual void animationFinished();
public:
	Campfire(int id, double x, double y, int firstImgID);
	void animate();
	virtual ~Campfire();
};

