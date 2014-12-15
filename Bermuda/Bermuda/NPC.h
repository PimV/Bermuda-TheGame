#pragma once
#include "Entity.h"
#include "Spawnpoint.h"
#include "IState.h"

class NPC :
	public virtual Entity
{
public:
	NPC(int id, int healthPoints, int attackPoints, int actionRange, Spawnpoint *spawnPoint);
	virtual ~NPC();

#pragma region Getters
	int getHeathPoints();
	int getAttackPoints();
	int getActionRange();
	Spawnpoint* getSpawnPoint();
	IState* getCurrentState();
#pragma endregion

#pragma region Setters
	void setHealthPoints(int healthPoints);
	void setAttackPoints(int attackPoints);
	void setActionRange(int actionRange);
	void setSpawnPoint(Spawnpoint *spawnPoint);
	void setCurrentState(IState* state);
#pragma endregion

private:
	int healthPoints, attackPoints, walkRange, actionRange, respawnTime, interactTime;
	bool destroyed, timeSinceDestroy, currentInteractTime;;
	Spawnpoint *spawnPoint;
	IState *currentState;
};