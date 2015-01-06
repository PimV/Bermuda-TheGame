#include "AggressiveBehaviour.h"
#include "PlayState.h"

AggressiveBehaviour::AggressiveBehaviour(StateMachine<Entity>* m_pStateMachine) :
	BaseBehaviour(m_pStateMachine)
{

}

void AggressiveBehaviour::executeAction()
{
	
	dynamic_cast<AttackingNPC*>( this->npc )->attack();
}

void AggressiveBehaviour::update(double dt)
{
	double diffX = PlayState::Instance()->getPlayer()->getCenterX() - this->npc->getCenterX();
	double diffY = PlayState::Instance()->getPlayer()->getCenterY() - this->npc->getCenterY();
	double distanceFromPlayer = sqrt((diffX * diffX) + (diffY * diffY));

	// TODO: look for a good way to stop the movement
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

AggressiveBehaviour::~AggressiveBehaviour()
{

}
