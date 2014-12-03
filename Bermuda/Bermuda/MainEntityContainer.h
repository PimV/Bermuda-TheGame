#pragma once
#include "ContainerType.h"
#include "IEntityContainer.h"
#include "DrawableContainer.h"
#include "AnimatingContainer.h"
#include "CollidableContainer.h"
#include "BackgroundContainer.h"
#include "InteractableContainer.h"
#include "MovableContainer.h"
#include "RespawnContainer.h"
#include "SpawnpointContainer.h"
#include "DestroyContainer.h"
#include <map>

class MainEntityContainer
{
public:
	MainEntityContainer();
	DrawableContainer* getDrawableContainer();
	AnimatingContainer* getAnimatingContainer();
	CollidableContainer* getCollidableContainer();
	BackgroundContainer* getBackgroundContainer();
	InteractableContainer* getInteractableContainer();
	RespawnContainer* getRespawnContainer();
	MovableContainer* getMovableContainer();
	SpawnpointContainer* getSpawnpointContainer();
	DestroyContainer* getDestroyContainer();

	virtual ~MainEntityContainer();

	void initContainerSizes(int mapHeight, int mapWidth);
	int getChunkSize();

private: 
	std::map<ContainerType, IEntityContainer*> m_container;
	const int chunkSize;
};

