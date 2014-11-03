#pragma once
#include "Entity.h"

class Spawnpoint :
	public virtual Entity
{
public:
	Spawnpoint(int id, double x, double y, int chunkSize);
	virtual ~Spawnpoint();
};

