#pragma once
#include "ientitycontainer.h"
#include "CollidableEntity.h"
class CollidableContainer :
	public IEntityContainer
{
public:
	CollidableContainer();

	void add(CollidableEntity* collidable);
	std::vector<CollidableEntity*> getContainer();

	virtual ~CollidableContainer();
private:
	std::vector<CollidableEntity*> m_container;
};

