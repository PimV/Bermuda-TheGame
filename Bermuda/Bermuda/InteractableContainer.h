#pragma once
#include "ientitycontainer.h"
#include "InteractableEntity.h"


class InteractableContainer :
	public IEntityContainer
{
public:
	InteractableContainer();

	void add(InteractableEntity* entity);
	std::vector<InteractableEntity*>* getChunk(int y, int x);

	void initChunks(int chunksY, int chunksX);
	void remove(InteractableEntity* entity);
	void cleanup();

	virtual ~InteractableContainer();
private:
	std::vector<std::vector<std::vector<InteractableEntity*>>> container;
};

