#include "Spawnpoint.h"
enum type
{
	RABBIT
};

Spawnpoint::Spawnpoint(int id, double x, double y, int chunkSize) 
	: Entity(id,x,y,chunkSize)
{
}

void Spawnpoint::Check()
{
	if (maxChilderen - curChilderen <= 0)
	{
		SpawnMob();
	}
}

void Spawnpoint::SpawnMob()
{
	
}

Spawnpoint::~Spawnpoint()
{
}
