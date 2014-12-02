#pragma once
#include "IEntityContainer.h"
#include "DrawableEntity.h"

class ParticleContainer :
	public IEntityContainer
{
public:
	ParticleContainer();
	
	std::vector<DrawableEntity*>* getChunk(int y, int x);	
	void initChunks(int chunksY, int chunksX);
	
	void add(DrawableEntity* entity);
	void remove(DrawableEntity* entity);

	virtual ~ParticleContainer();
private: 
	std::vector<std::vector<std::vector<DrawableEntity*>>> container;
};

