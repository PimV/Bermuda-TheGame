#pragma once
#include "ientitycontainer.h"
#include "Collidable.h"
class CollidableContainer :
	public IEntityContainer
{
public:
	CollidableContainer();


	void add(Collidable* collidable);
	std::vector<Collidable*> getContainer();

	virtual ~CollidableContainer();
private:
	std::vector<Collidable*> m_container;
};

