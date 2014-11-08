#pragma once
#include "ientitycontainer.h"
#include "DrawableEntity.h"
class DrawableContainer :
	public IEntityContainer
{
public:
	DrawableContainer();

	std::vector<DrawableEntity*>* getChunk(int y, int x);	
	void initChunks(int chunksY, int chunksX);

	void cleanup();

	void add(DrawableEntity* entity);
	void remove(DrawableEntity* entity);

	virtual ~DrawableContainer();
private: 
	std::vector<std::vector<std::vector<DrawableEntity*>>> container;
};

