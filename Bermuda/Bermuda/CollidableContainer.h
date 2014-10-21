#pragma once
#include "ientitycontainer.h"
#include "CollidableEntity.h"
class CollidableContainer :
	public IEntityContainer
{
public:
	//CollidableContainer();
	CollidableContainer();

	void add(CollidableEntity* collidable);
	std::vector<std::vector<std::vector<CollidableEntity*>>>* getContainer();
	std::vector<CollidableEntity*>* getChunk(int y, int x);

	void initChunks(int chunksY, int chunksX);

	virtual ~CollidableContainer();
private:
	//std::vector<CollidableEntity*> m_container;
	std::vector<std::vector<std::vector<CollidableEntity*>>> container;
};