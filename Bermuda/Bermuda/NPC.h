#pragma once
#include "Entity.h"
#include "Spawnpoint.h"
//#include "BaseBehaviour.h"
class BaseBehaviour;

class NPC :
	public virtual Entity
{
private:
	int healthPoints, attackPoints, respawnTime, interactTime;
	int  walkRange, actionRange, attackRange;
	long timeSinceDestroy, currentInteractTime;
	bool destroyed;
	Spawnpoint *spawnPoint;

protected:
	//StateMachine<Entity>* m_pStateMachine;
	BaseBehaviour* behaviour;

public:
	NPC(int id, int healthPoints, int attackPoints, int actionRange, Spawnpoint *spawnPoint);
	virtual ~NPC();

#pragma region Getters
	int getHealthPoints();
	int getAttackPoints();
	int getActionRange();
	int getAttackRange();
	Spawnpoint* getSpawnPoint();

	//StateMachine<Entity>* GetFSM()const{ return m_pStateMachine; }
	BaseBehaviour* getBehaviour();
#pragma endregion

#pragma region Setters
	void setHealthPoints(int healthPoints);
	void setAttackPoints(int attackPoints);
	void setActionRange(int actionRange);
	void setAttackRange(int attackRange);
	void setSpawnPoint(Spawnpoint *spawnPoint);
#pragma endregion

};