#include "DestroyContainer.h"


DestroyContainer::DestroyContainer()
{
}

std::vector<Entity*>* DestroyContainer::getContainer() {
	return &this->container;
}

void DestroyContainer::add(Entity* interactable)
{
	this->container.push_back(interactable);
}

void DestroyContainer::remove(Entity* entity)
{
	std::vector<Entity*>* vec = &this->container;
	std::vector<Entity*>::iterator it = std::find(vec->begin(), vec->end(), entity);

	if (it != vec->end()) {
		vec->erase(it);
	}
}

void DestroyContainer::destroyAllEntities()
{
	if (container.size() > 0)
	{
		std::vector<Entity*>::iterator it;
		for (it = container.begin(); it != container.end();)
		{
			delete *it;
			it = container.erase(it);
		}
	}
}

DestroyContainer::~DestroyContainer()
{
}
