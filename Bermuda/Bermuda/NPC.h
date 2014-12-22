#pragma once
#include "Entity.h"
#include "Spawnpoint.h"
#include "StateMachine.h"

class NPC :
	public virtual Entity
{
private:
	int healthPoints, attackPoints, walkRange, actionRange, respawnTime, interactTime;
	bool destroyed, timeSinceDestroy, currentInteractTime;;
	Spawnpoint *spawnPoint;

public:
	NPC(int id, int healthPoints, int attackPoints, int actionRange, Spawnpoint *spawnPoint);
	virtual ~NPC();

#pragma region Getters
	int getHealthPoints();
	int getAttackPoints();
	int getActionRange();
	Spawnpoint* getSpawnPoint();
#pragma endregion

#pragma region Setters
	void setHealthPoints(int healthPoints);
	void setAttackPoints(int attackPoints);
	void setActionRange(int actionRange);
	void setSpawnPoint(Spawnpoint *spawnPoint);
#pragma endregion
};