#pragma once
#include "AnimatingEntity.h"
#include "CollidableEntity.h"
#include "InteractableEntity.h"
#include "ParticleEngine.h"

class Campfire :
	public AnimatingEntity, public CollidableEntity
{
private:
	double creationTime;
	double destroyTime;
	ParticleEngine* particleEngine;
protected:
	virtual void animationFinished();
public:
	Campfire(int id, double x, double y, int firstImgID);
	void animate(double dt);
	virtual ~Campfire();
};

