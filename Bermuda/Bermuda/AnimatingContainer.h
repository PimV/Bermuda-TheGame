#pragma once
#include "IEntityContainer.h"
#include "AnimatingEntity.h"

class AnimatingContainer :
	public IEntityContainer
{
public:
	AnimatingContainer();
	std::vector<AnimatingEntity*>* getChunk(int y, int x);
	void initChunks(int chunksY, int chunksX);

	void add(AnimatingEntity* entity);
	void remove(AnimatingEntity* entity);

	virtual ~AnimatingContainer();
private:
	std::vector<std::vector<std::vector<AnimatingEntity*>>> container;
};

