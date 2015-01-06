#include "InteractableNPC.h"

InteractableNPC::InteractableNPC(int id, int healthPoints, int attackPoints, int actionRange, int attackRange, Spawnpoint *spawnPoint, int interactStartX, int interactStartY, int interactWitdh, int interactHeight, long attackTime) :
	NPC( id, actionRange, attackRange, spawnPoint ),
	Entity( id, spawnPoint->getX(), spawnPoint->getY() ),
	InteractableEntity(id, spawnPoint->getX(), spawnPoint->getY(), interactStartX, interactStartY, interactWitdh, interactHeight ),
	AttackingNPC(attackTime)
{
	this->interactTime = 0;
	this->currentInteractTime = 0;
	this->animationType = AnimationEnumType::Attack;

	this->healthPoints = healthPoints;
	this->currentHealthPoints = healthPoints;
	this->attackPoints = attackPoints;
}

#pragma region Getters
int InteractableNPC::getHealthPoints()
{
	return this->currentHealthPoints;
}

int InteractableNPC::getAttackPoints()
{
	return this->attackPoints;
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
#pragma endregion

bool InteractableNPC::isNpcMaxHealth()
{
	if (this->currentHealthPoints < this->healthPoints)
		return false;

	return true;
}

void InteractableNPC::attack()
{
	if( this->checkAttackTimes())
	{
		PlayState::Instance()->getPlayer()->setHealth( ( PlayState::Instance()->getPlayer()->getHealth() - this->getAttackPoints() ) );
	}
}

InteractableNPC::~InteractableNPC(void)
{
}
