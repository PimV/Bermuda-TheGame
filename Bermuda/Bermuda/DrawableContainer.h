#pragma once
#include "IEntityContainer.h"
#include "DrawableEntity.h"

class DrawableContainer :
	public IEntityContainer
{
public:
	DrawableContainer();
	
	std::vector<DrawableEntity*>* getChunk(int y, int x);	
	void initChunks(int chunksY, int chunksX);
	
	void add(DrawableEntity* entity);
	void remove(DrawableEntity* entity);
	void cleanup();

	virtual ~DrawableContainer();
private: 
	std::vector<std::vector<std::vector<DrawableEntity*>>> container;
};

