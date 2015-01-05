#pragma once
#include "NPC.h"
#include "InteractableEntity.h"
#include "Weapon.h"

class InteractableNPC :
	public NPC,
	public InteractableEntity
{
	private:
		//
	protected:
		int healthPoints, attackPoints, respawnTime, interactTime;
		int  walkRange, actionRange, attackRange;

	public:
		InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, int attackRange, Spawnpoint *spawnPoint, int interactStartX, int interactStartY, int interactWitdh, int interactHeight);
		virtual ~InteractableNPC(void);

		int getHealthPoints();
		int getAttackPoints();
		int getActionRange();
		int getAttackRange();

		void setHealthPoints(int healthPoints);
		void setAttackPoints(int attackPoints);
		void setActionRange(int actionRange);
		void setAttackRange(int attackRange);
};
