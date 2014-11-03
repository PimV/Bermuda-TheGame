#pragma once
#include "ientitycontainer.h"
#include "InteractableEntity.h"


class RespawnContainer :
	public IEntityContainer
{
public:
	RespawnContainer();

	void add(InteractableEntity* entity);
	void remove(InteractableEntity* entity);

	std::vector<InteractableEntity*>* getContainer();

	virtual ~RespawnContainer();
private:
	std::vector<InteractableEntity*> container;
};

