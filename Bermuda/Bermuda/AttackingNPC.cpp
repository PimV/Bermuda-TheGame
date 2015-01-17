#include "AttackingNPC.h"
#include "GameTimer.h"

AttackingNPC::AttackingNPC(int attackPoints, int attackRange, long attackTime)
{
	this->attackPoints = attackPoints;
	this->attackRange = attackRange;
	this->attackTime = attackTime;
	this->currentAttackTime = 0;
}

int AttackingNPC::getAttackPoints()
{
	return this->attackPoints;
}
int AttackingNPC::getAttackRange()
{
	return this->attackRange;
}

void AttackingNPC::setAttackPoints(int attackPoints)
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

void AttackingNPC::setAttackRange(int attackRange)
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

bool AttackingNPC::checkAttackTimes()
{
	this->currentAttackTime += static_cast<long>( GameTimer::Instance()->getFrameTime() );
	if (this->currentAttackTime > this->attackTime )
	{
		this->currentAttackTime = 0;
		return true;
	}
	return false;
}

void AttackingNPC::attack()
{
	if( this->checkAttackTimes())
	{
		PlayState::Instance()->getPlayer()->setHealth( ( PlayState::Instance()->getPlayer()->getHealth() - this->getAttackPoints() ) );
	}
}

AttackingNPC::~AttackingNPC(void)
{
	this->attackTime = 0;
	this->currentAttackTime = 0;
}