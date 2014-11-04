#include "Spawnpoint.h"
#include "Rabbit.h"
#include "PlayState.h"
#include <iostream>

enum spawnType
{
	RABBIT,
	WASP
};

Spawnpoint::Spawnpoint(int type, double x, double y, int chunkSize) 
: Entity(type, x, y, chunkSize)
{
	this->type = type;
}

void Spawnpoint::init()
{
	curChilderen = 0;
	if (type == RABBIT)
	{
		maxChilderen = 5;
	}
	if (type == WASP)
	{
		maxChilderen = 8;
	}
}

void Spawnpoint::spawnMob()
{
	if (curChilderen < maxChilderen)
	{
		if (type == RABBIT)
		{
			//rabbits.push_back(new Rabbit(1001, this->getChunkSize(), this, GameStateManager::Instance(), PlayState::Instance()->getMainEntityContainer));
		}
		if (type == WASP)
		{
			//wasps.push_back(new Wasp(2001, this->getChunkSize(), this, GameStateManager::Instance(), PlayState::Instance()->getMainEntityContainer));
		}

	}
}

Spawnpoint::~Spawnpoint()
{
}
