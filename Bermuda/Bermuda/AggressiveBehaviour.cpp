#include "AggressiveBehaviour.h"
#include "PlayState.h"
#include <iostream>

AggressiveBehaviour::AggressiveBehaviour(StateMachine<Entity>* m_pStateMachine) :
	BaseBehaviour(m_pStateMachine)
{
	this->m_pStateMachine = m_pStateMachine;
	this->npc = dynamic_cast<NPC*>( m_pStateMachine->getOwner() );
	this->setFsmToDefaultState();
}

void AggressiveBehaviour::executeAction()
{
	std::cout << "NPC is now attacking player \n";
}

void AggressiveBehaviour::update(double dt)
{
	double diffX = PlayState::Instance()->getPlayer()->getCenterX() - this->npc->getCenterX();
	double diffY = PlayState::Instance()->getPlayer()->getCenterY() - this->npc->getCenterY();
	double distanceFromPlayer = sqrt((diffX * diffX) + (diffY * diffY));

	// TODO: look for a good way to stop the movement
	//if ( this->m_pStateMachine->getCurrentState() == AggressiveState::Instance() && distanceFromPlayer < this->npc->getAttackRange() )
	if ( this->m_pStateMachine->getCurrentState() == AggressiveState::Instance() && distanceFromPlayer < 5 )
	{
		this->executeAction();
	}
	else
	{
		if (this->m_pStateMachine->getCurrentState() == WanderAround::Instance() && distanceFromPlayer <= this->npc->getActionRange() )
		{
			this->setFsmToAggresdsiveState();
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
	this->npc = nullptr;
}
