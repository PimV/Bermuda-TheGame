#include "DefensiveBehaviour.h"
#include "PlayState.h"
#include <iostream>

DefensiveBehaviour::DefensiveBehaviour(StateMachine<Entity>* m_pStateMachine) : 
	BaseBehaviour(m_pStateMachine)
{
}

void DefensiveBehaviour::executeAction()
{
	std::cout << "NPC is now Attacking player \n";
}

void DefensiveBehaviour::update(double dt)
{
	double diffX = PlayState::Instance()->getPlayer()->getCenterX() - this->npc->getSpawnPoint()->getCenterX();
	double diffY = PlayState::Instance()->getPlayer()->getCenterY() - this->npc->getSpawnPoint()->getCenterY();
	double distanceFromPlayer = sqrt((diffX * diffX) + (diffY * diffY));

	// TODO: look for a good way to stop the movement
	//if ( this->m_pStateMachine->getCurrentState() == AggressiveState::Instance() && distanceFromPlayer < this->npc->getAttackRange() )
	if ( this->m_pStateMachine->getCurrentState() == AggressiveState::Instance() && distanceFromPlayer < 5 )
	{
		this->executeAction();
	}
	else
	{
		//if (this->m_pStateMachine->getCurrentState() == WanderAround::Instance() && distanceFromPlayer <= this->npc->getActionRange() )
		if (this->m_pStateMachine->getCurrentState() == WanderAround::Instance() && distanceFromPlayer <= 50 )
		{
			std::cout << "NPC is now Defending object \n";
			this->setFsmToAggresdsiveState();
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
