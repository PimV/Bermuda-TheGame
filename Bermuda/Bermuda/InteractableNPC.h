#pragma once
#include "PlayState.h"
#include "InteractableEntity.h"
#include "NPC.h"
#include "AttackingNPC.h"
#include "Weapon.h"

class InteractableNPC :
	public NPC,
	public InteractableEntity,
	public AttackingNPC
{
	private:
		//
	protected:
		int healthPoints, attackPoints;

		void addToContainers();
		void removeFromConainers();

	public:
		InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, int attackRange, Spawnpoint *spawnPoint, int interactStartX, int interactStartY, int interactWitdh, int interactHeight, long attackTime);
		virtual ~InteractableNPC(void);

		int getHealthPoints();
		int getAttackPoints();

		void setHealthPoints(int healthPoints);
		void setAttackPoints(int attackPoints);

		virtual void attack();
};
