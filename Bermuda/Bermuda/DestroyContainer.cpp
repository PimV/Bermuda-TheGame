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
	while (!this->container.empty())
	{
		Entity* entity = this->container.back();
		this->container.pop_back();
		delete entity;
		entity = nullptr;
	}
}

void DestroyContainer::cleanup()
{
	this->destroyAllEntities();
}

DestroyContainer::~DestroyContainer()
{
	this->cleanup();
}
