#include "RespawnContainer.h"

RespawnContainer::RespawnContainer()
{
}

std::vector<InteractableEntity*>* RespawnContainer::getContainer() {
	return &this->container;
}

void RespawnContainer::add(InteractableEntity* interactable) 
{
	this->container.push_back(interactable);
}

void RespawnContainer::remove(InteractableEntity* entity)
{
	std::vector<InteractableEntity*>* vec = &this->container;
	std::vector<InteractableEntity*>::iterator it = std::find(vec->begin(), vec->end(), entity);

	if (it != vec->end()) {
		vec->erase(it);
	}
}

RespawnContainer::~RespawnContainer(void)
{
}
