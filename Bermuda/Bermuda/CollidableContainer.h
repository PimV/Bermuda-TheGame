#pragma once
#include "ientitycontainer.h"
#include "CollidableEntity.h"

class CollidableContainer :
	public IEntityContainer
{
public:
	CollidableContainer();

	void add(CollidableEntity* collidable);
	std::vector<CollidableEntity*>* getChunk(int y, int x);

	void initChunks(int chunksY, int chunksX);
	void remove(CollidableEntity* entity);

	virtual ~CollidableContainer();
private:
	std::vector<std::vector<std::vector<CollidableEntity*>>> container;
};