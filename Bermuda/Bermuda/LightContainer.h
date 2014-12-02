#pragma once
#include "IEntityContainer.h"
#include "LightEntity.h"
class LightContainer :
	public IEntityContainer
{
public:
	LightContainer();
	virtual ~LightContainer();

	void add(LightEntity* collidable);
	std::vector<LightEntity*>* getChunk(int y, int x);

	void initChunks(int chunksY, int chunksX);
	void remove(LightEntity* entity);
private:
	std::vector<std::vector<std::vector<LightEntity*>>> container;
};

