#pragma once
#include "ContainerType.h"
#include "IEntityContainer.h"
#include "DrawableContainer.h"
#include "CollidableContainer.h"
#include "BackgroundContainer.h"
#include "InteractableContainer.h"
#include "MovableContainer.h"
#include "RespawnContainer.h"
#include "SpawnpointContainer.h"
#include <map>

class MainEntityContainer
{
public:
	MainEntityContainer();
	DrawableContainer* getDrawableContainer();
	CollidableContainer* getCollidableContainer();
	BackgroundContainer* getBackgroundContainer();
	InteractableContainer* getInteractableContainer();
	RespawnContainer* getRespawnContainer();
	MovableContainer* getMovableContainer();
	SpawnpointContainer* getSpawnpointContainer();

	virtual ~MainEntityContainer();

	void initContainerSizes(int chunksY, int chunksX);


private: 
	std::map<ContainerType, IEntityContainer*> m_container;
};

