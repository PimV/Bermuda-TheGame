#pragma once
#include "Entity.h"
#include "Spawnpoint.h"
#include "StateMachine.h"

class Player;

class NPC :
	public virtual Entity
{
private:
	int healthPoints, attackPoints, walkRange, actionRange;
	bool destroyed, timeSinceDestroy;

public:
	NPC(int id, Spawnpoint *spawnPoint);
	virtual ~NPC();

	Spawnpoint* getSpawnPoint();
	void setSpawnPoint(Spawnpoint *spawnPoint);

protected:
	Spawnpoint *spawnPoint;

private:

};

