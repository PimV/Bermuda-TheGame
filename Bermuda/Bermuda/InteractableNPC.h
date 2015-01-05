#pragma once
#include "NPC.h"
#include "InteractableEntity.h"
#include "Weapon.h"

class InteractableNPC :
	public NPC,
	public InteractableEntity
{
public:
	InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, Spawnpoint *spawnPoint, int interactStartX, int interactStartY, int interactWitdh, int interactHeight);
	virtual ~InteractableNPC(void);

	int getHealthPoints();
	int getAttackPoints();
	int getActionRange();

	void setHealthPoints(int healthPoints);
	void setAttackPoints(int attackPoints);
	void setActionRange(int actionRange);

protected:
	int healthPoints, attackPoints, walkRange, actionRange;

private:
	//
};
