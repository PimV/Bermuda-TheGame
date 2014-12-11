#pragma once
#include "IEntityContainer.h"
#include "Entity.h"

class DestroyContainer :
	public IEntityContainer
{
public:
	DestroyContainer();
	void add(Entity* entity);
	void remove(Entity* entity);
	void destroyAllEntities();
	void cleanup();

	std::vector<Entity*>* getContainer();
	virtual ~DestroyContainer();
private:
	std::vector<Entity*> container;
};

