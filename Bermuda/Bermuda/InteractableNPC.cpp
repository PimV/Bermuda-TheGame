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
	this->attackPoints = attackPoints;
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
#pragma endregion

void InteractableNPC::attack()
{
	if( this->checkAttackTimes())
	{
		PlayState::Instance()->getPlayer()->setHealth( ( PlayState::Instance()->getPlayer()->getHealth() - this->getAttackPoints() ) );
	}
}

void InteractableNPC::addToContainers()
{
	//PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	//PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	//PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
	//PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void InteractableNPC::removeFromConainers()
{
	//PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	//PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	//PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	//PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}

InteractableNPC::~InteractableNPC(void)
{
}
