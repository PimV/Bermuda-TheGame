#include "DefensiveBehaviour.h"
#include "PlayState.h"
#include <iostream>

DefensiveBehaviour::DefensiveBehaviour(StateMachine<Entity>* m_pStateMachine) : 
	BaseBehaviour(m_pStateMachine)
{

}

void DefensiveBehaviour::executeAction()
{
	dynamic_cast<AttackingNPC*>( this->npc )->attack();
}

void DefensiveBehaviour::update(double dt)
{
	double diffX = PlayState::Instance()->getPlayer()->getCenterX() - this->npc->getCenterX();
	double diffY = PlayState::Instance()->getPlayer()->getCenterY() - this->npc->getCenterY();
	double distanceFromPlayer = sqrt((diffX * diffX) + (diffY * diffY));

	// TODO: look for a good way to stop the movement and add health check
	if ( this->m_pStateMachine->getCurrentState() == AggressiveState::Instance() && distanceFromPlayer < this->npc->getAttackRange() )
	{
		this->executeAction();
	}
	else
	{
		if (this->m_pStateMachine->getCurrentState() == WanderState::Instance() && distanceFromPlayer <= this->npc->getActionRange() )
		{
			this->setFsmToAggressiveState();
		}
		else if (this->m_pStateMachine->getCurrentState() == AggressiveState::Instance() && distanceFromPlayer >= ( this->npc->getActionRange() * 2) )
		{
			this->setFsmToWanderState();
		}

		this->m_pStateMachine->update(dt);
	}
}

DefensiveBehaviour::~DefensiveBehaviour(void)
{

}
