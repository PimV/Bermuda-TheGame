#pragma once
#include "Entity.h"

class Spawnpoint;

class NPC :
	public Entity
{
public:
	NPC(int id, int healthPoints, int attackPoints, int walkRange, int actionRange, Spawnpoint *spawnPoint);
	virtual ~NPC(void);
	
	// Getters
	int getHeathPoints();
	int getAttackPoints();
	int getWalkRange();
	int getActionRange();
	int getSpawnPoint();
	 
	// Setters
	void setHealthPoints(int healthPoints);
	void setAttackPoints(int attackPoints);
	void setWalkRange(int walkRange);
	void setActionRange(int actionRange);
	void setSpawnPoint(Spawnpoint *spawnPoint);

private:
	int healthPoints, attackPoints, walkRange, actionRange;
	Spawnpoint *spawnPoint;
};