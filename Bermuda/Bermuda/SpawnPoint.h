#pragma once
#include "Entity.h"

class Spawnpoint :
	public Entity
{
public:
	Spawnpoint(int id, int x, int y, int chunkSize);
	virtual ~Spawnpoint();
};

