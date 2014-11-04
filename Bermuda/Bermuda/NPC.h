#pragma once
#include "Entity.h"
#include "Spawnpoint.h"
#include "CollidableContainer.h"

class NPC :
	public virtual Entity
{
public:
	NPC(int id, int chunkSize, int healthPoints, int attackPoints, int walkRange, int actionRange, Spawnpoint *spawnPoint);
	virtual ~NPC(void);

#pragma region Getters
	int getHeathPoints();
	int getAttackPoints();
	int getWalkRange();
	int getActionRange();
	Spawnpoint* getSpawnPoint();
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
	bool destroyed, respawnTime, interactTime, timeSinceDestroy, currentInteractTime;;
	Spawnpoint *spawnPoint;

	virtual void update(double dt) = 0;
	virtual void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt) = 0;
	virtual void StopAnimation() = 0;
	virtual void setPosition() = 0;
	virtual bool checkCollision(CollidableContainer* container) = 0;
	virtual void calculateMovingDirectionAndMove(double dt) = 0;

};