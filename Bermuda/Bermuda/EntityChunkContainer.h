#pragma once
#include "header_loader.h"
#include "Entity.h"
#include <vector>

class EntityChunkContainer
{
private:
	std::vector<std::vector<std::vector<Entity*>>> container;
public:
	EntityChunkContainer();

	void initChunks(int ChunksY, int chunksX);
	void add(Entity* entity);
	void remove(Entity* entity);

	std::vector<Entity*>* getChunk(int y, int x);

	virtual ~EntityChunkContainer();
};

