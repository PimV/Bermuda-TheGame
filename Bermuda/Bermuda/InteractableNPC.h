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
	InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, Spawnpoint *spawnPoint, int interactStartX, int interactStartY, int interactWitdh, int interactHeight);
	virtual ~InteractableNPC(void);

	#pragma region Getters
	int getHealthPoints();
	int getAttackPoints();
	int getActionRange();
	#pragma endregion

	#pragma region Setters
	void setHealthPoints(int healthPoints);
	void setAttackPoints(int attackPoints);
	void setActionRange(int actionRange);
	#pragma endregion

	void interact(Player* player);

protected:
	int healthPoints, attackPoints, walkRange, actionRange;

private:
	//
};
