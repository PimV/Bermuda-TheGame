#pragma once
#include "IEntityContainer.h"
#include "SpawnPoint.h"

class SpawnpointContainer :
	public IEntityContainer
{
public:
	SpawnpointContainer();
	
	void add(Spawnpoint* collidable);
	std::vector<Spawnpoint*>* getChunk(int y, int x);
	void initChunks(int chunksY, int chunksX);
	void remove(Spawnpoint* entity);

	void cleanup();

	~SpawnpointContainer();
private:
	std::vector<std::vector<std::vector<Spawnpoint*>>> container;
};

