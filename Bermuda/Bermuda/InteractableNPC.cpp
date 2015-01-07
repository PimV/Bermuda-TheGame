#include "InteractableNPC.h"

InteractableNPC::InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, int attackRange, Spawnpoint *spawnPoint, int interactStartX, int interactStartY, int interactWitdh, int interactHeight, long attackTime) :
	NPC( id, actionRange, attackRange, spawnPoint ),
	Entity( id, spawnPoint->getX(), spawnPoint->getY() ),
	InteractableEntity(id, spawnPoint->getX(), spawnPoint->getY(), interactStartX, interactStartY, interactWitdh, interactHeight ),
	AttackingNPC(attackPoints, attackRange, attackTime)
{
	this->interactTime = 0;
	this->currentInteractTime = 0;
	this->animationType = AnimationEnumType::Attack;

	this->healthPoints = healthPoints;
	this->currentHealthPoints = healthPoints;
	this->actionRange = actionRange;
}

#pragma region Getters
int InteractableNPC::getHealthPoints()
{
	return this->currentHealthPoints;
}

int InteractableNPC::getActionRange()
{
	return this->actionRange;
}
#pragma endregion

#pragma region Setters
void InteractableNPC::setHealthPoints(int healthPoints)
{
	if (healthPoints < 0)
	{
		this->currentHealthPoints = 0;
	}
	else if (healthPoints > this->healthPoints)
	{
		this->currentHealthPoints = this->healthPoints;
	}
	else
	{
		this->currentHealthPoints = healthPoints;
	}
}
#pragma endregion

bool InteractableNPC::isNpcMaxHealth()
{
	return (this->currentHealthPoints < this->healthPoints);
}

InteractableNPC::~InteractableNPC(void)
{
}
