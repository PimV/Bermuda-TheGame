#pragma once
#include "Entity.h"

class Spawnpoint;

class NPC :
	public Entity
{
public:
	NPC(int id, int chunkSize, int healthPoints, int attackPoints, int walkRange, int actionRange, Spawnpoint *spawnPoint);
	virtual ~NPC(void);

	void walk();

#pragma region Getters
	int getHeathPoints();
	int getAttackPoints();
	int getWalkRange();
	int getActionRange();
	int getSpawnPoint();
#pragma endregion

#pragma region Setters
	void setHealthPoints(int healthPoints);
	void setAttackPoints(int attackPoints);
	void setWalkRange(int walkRange);
	void setActionRange(int actionRange);
	void setSpawnPoint(Spawnpoint *spawnPoint);
#pragma endregion

private:
	int healthPoints, attackPoints, walkRange, actionRange;
	bool walking;
	Spawnpoint *spawnPoint;
};