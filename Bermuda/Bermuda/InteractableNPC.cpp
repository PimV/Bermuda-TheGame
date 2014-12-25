#include "InteractableNPC.h"

InteractableNPC::InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, Spawnpoint *spawnPoint, int interactStartX, int interactStartY, int interactWitdh, int interactHeight) :
	NPC( id, spawnPoint ),
	Entity( id, spawnPoint->getX(), spawnPoint->getY() ),
	InteractableEntity(id, spawnPoint->getX(), spawnPoint->getY(), interactStartX, interactStartY, interactWitdh, interactHeight )
{
	//this->interactTime = 0;
	//sthis->currentInteractTime = 0;
	this->animationType = AnimationEnumType::Attackable;
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
#pragma endregion

InteractableNPC::~InteractableNPC(void)
{
}
