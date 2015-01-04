#include "AttackingNPC.h"
#include "GameTimer.h"

AttackingNPC::AttackingNPC(int attackTime)
{
	this->attackTime = attackTime;
	this->currentAttackTime = 0;
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

AttackingNPC::~AttackingNPC(void)
{
	this->attackTime = 0;
	this->currentAttackTime = 0;
}