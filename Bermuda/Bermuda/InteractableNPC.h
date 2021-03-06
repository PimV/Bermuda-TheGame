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
	protected:
		int healthPoints, currentHealthPoints;
		int actionRange;

	public:
		InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, int attackRange, Spawnpoint *spawnPoint, int interactStartX, int interactStartY, int interactWitdh, int interactHeight, long attackTime);
		virtual ~InteractableNPC();

		int getHealthPoints();
		void setHealthPoints(int healthPoints);

		int getActionRange();

		bool isNpcMaxHealth();
};
