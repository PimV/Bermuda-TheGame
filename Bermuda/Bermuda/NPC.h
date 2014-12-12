#pragma once
#include "Entity.h"
#include "Spawnpoint.h"
#include "InteractableEntity.h"
class Player;

class NPC :
	public virtual Entity,
	public InteractableEntity
{
public:
	NPC(int id, int healthPoints, int attackPoints, int actionRange, Spawnpoint *spawnPoint);
	virtual ~NPC();

#pragma region Getters
	int getHeathPoints();
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

	void interact(Player* player);

protected:
	int healthPoints, attackPoints, walkRange, actionRange;
	Spawnpoint *spawnPoint;

private:
	//int healthPoints, attackPoints, walkRange, actionRange, respawnTime, interactTime;
	//bool destroyed, timeSinceDestroy, currentInteractTime;

	/*
	int healthPoints, attackPoints, walkRange, actionRange;
	Spawnpoint *spawnPoint;
	*/
};