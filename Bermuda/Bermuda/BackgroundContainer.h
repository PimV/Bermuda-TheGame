#pragma once
#include "IEntityContainer.h"
#include "DrawableEntity.h"
#include <vector>
class BackgroundContainer :
	public IEntityContainer
{
public:
	BackgroundContainer();

	void add(DrawableEntity* entity);
	std::vector<DrawableEntity*>* getChunk(int y, int x);
	
	void initChunks(int chunksY, int chunksX);
	void remove(DrawableEntity* entity);
	void cleanup();

	virtual ~BackgroundContainer();
private:
	std::vector<std::vector<std::vector<DrawableEntity*>>> container;
};

