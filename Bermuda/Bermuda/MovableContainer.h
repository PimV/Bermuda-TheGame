#pragma once
#include "ientitycontainer.h"
#include "MovableEntity.h"

class MovableContainer :
	public IEntityContainer
{
public:
	MovableContainer();

	void add(MovableEntity* collidable);
	std::vector<MovableEntity*>* getChunk(int y, int x);

	void initChunks(int chunksY, int chunksX);
	void remove(MovableEntity* entity);

	virtual ~MovableContainer();
private:
	std::vector<std::vector<std::vector<MovableEntity*>>> container;
};

