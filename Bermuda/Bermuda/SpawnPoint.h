#pragma once
#include "Entity.h"

class Spawnpoint :
	public Entity
{
public:
	Spawnpoint(int id, double x, double y, int chunkSize);
	virtual ~Spawnpoint();
};

