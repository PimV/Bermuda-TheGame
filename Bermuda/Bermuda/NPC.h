#pragma once
#include "entity.h"
#include "spawnpoint.h"
class NPC :
	public Entity
{
public:
	NPC(int healthPoints, int attackPoints, int walkRange, int actionRange, SpawnPoint spawnPoint);
	virtual ~NPC(void);
	
	// Getters
	virtual int getHeathPoints() = 0;
	virtual int getAttackPoints() = 0;
	virtual int getWalkRange() = 0;
	virtual int getActionRange() = 0;
	virtual int getSpawnPoint() = 0;
	 
	// Setters
	virtual void setHealthPoints(int healthPoints) = 0;
	virtual void setAttackPoints(int attackPoints) = 0;
	virtual void setWalkRange(int walkRange) = 0;
	virtual void setActionRange(int actionRange) = 0;
	virtual void setSpawnPoint(int spawnPoint) = 0;

private:
	int _healthPoints, _attackPoints, _walkRange, _actionRange;
	SpawnPoint _spawnPoint;
};