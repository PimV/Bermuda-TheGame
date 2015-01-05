#include "InteractableNPC.h"

InteractableNPC::InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, int attackRange, Spawnpoint *spawnPoint, int interactStartX, int interactStartY, int interactWitdh, int interactHeight) :
	NPC( id, spawnPoint ),
	Entity( id, spawnPoint->getX(), spawnPoint->getY() ),
	InteractableEntity(id, spawnPoint->getX(), spawnPoint->getY(), interactStartX, interactStartY, interactWitdh, interactHeight )
{
	this->interactTime = 0;
	this->currentInteractTime = 0;
	this->animationType = AnimationEnumType::Attack;
}

#pragma region Getters
int InteractableNPC::getHealthPoints()
{
	return this->healthPoints;
}

int InteractableNPC::getAttackPoints()
{
	return this->attackPoints;
}

int InteractableNPC::getActionRange()
{
	return this->actionRange;
}

int InteractableNPC::getAttackRange()
{
	return this->attackRange;
}
#pragma endregion

#pragma region Setters
void InteractableNPC::setHealthPoints(int healthPoints)
{
	if (healthPoints < 0)
	{
		this->healthPoints = 0;
	}
	else
	{
		this->healthPoints = healthPoints;
	}
}

void InteractableNPC::setAttackPoints(int attackPoints)
{
	if (attackPoints < 0)
	{
		this->attackPoints = 0;
	}
	else
	{
		this->attackPoints = attackPoints;
	}
}

void InteractableNPC::setActionRange(int actionRange)
{
	if (actionRange < 0)
	{
		this->actionRange = 0;
	}
	else
	{
		this->actionRange = actionRange;
	}
}

void InteractableNPC::setAttackRange(int attackRange)
{
	if (attackRange < 0)
	{
		this->attackRange = 0;
	}
	else
	{
		this->attackRange = attackRange;
	}
}
#pragma endregion

InteractableNPC::~InteractableNPC(void)
{
}
