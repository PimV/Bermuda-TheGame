#pragma once
#include "Entity.h"
#include "BaseSpawnPoint.h"

class Spawnpoint :
	public virtual Entity,
	public BaseSpawnPoint
{
public:
	Spawnpoint(int type, double x, double y, int chunkSize);
	virtual ~Spawnpoint();
};

