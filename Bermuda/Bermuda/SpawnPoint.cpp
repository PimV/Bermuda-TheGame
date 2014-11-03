#include "Spawnpoint.h"
enum type
{
	RABBIT
};

Spawnpoint::Spawnpoint(int id) : Entity(id)
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
