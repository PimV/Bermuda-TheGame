#pragma once
#include "NPC.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "InteractableEntity.h"
#include "Weapon.h"

class InteractableNPC :
	public NPC,
	public InteractableEntity
{
public:
	InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, Spawnpoint *spawnPoint);
	virtual ~InteractableNPC(void);

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
	//
};
