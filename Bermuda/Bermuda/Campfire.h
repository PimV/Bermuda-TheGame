#pragma once
#include "AnimatingEntity.h"
#include "CollidableEntity.h"
#include "InteractableEntity.h"
//#include "ParticleEngine.h"
class ParticleEngine;

class Campfire :
	public AnimatingEntity, public CollidableEntity
{
private:
	double creationTime;
	double lifeTime;
	ParticleEngine* pe;
public:
	Campfire(int id, double x, double y, int firstImgID);
	void animate();
	void setParticleEngine(ParticleEngine* _pe);
	virtual ~Campfire();
};

