#include "EvasiveBehaviour.h"
#include <iostream>

EvasiveBehaviour::EvasiveBehaviour(StateMachine<Entity>* m_pStateMachine) : 
	BaseBehaviour(m_pStateMachine)
{

}

void EvasiveBehaviour::executeAction()
{
	
}

void EvasiveBehaviour::update(double dt)
{
	double diffX = PlayState::Instance()->getPlayer()->getCenterX() - this->npc->getCenterX();
	double diffY = PlayState::Instance()->getPlayer()->getCenterY() - this->npc->getCenterY();
	double distanceFromPlayer = sqrt((diffX * diffX) + (diffY * diffY));

	if (this->m_pStateMachine->getCurrentState() == WanderState::Instance() && distanceFromPlayer <= this->npc->getActionRange())
	{
		this->m_pStateMachine->changeState(FleeingState::Instance());
	}
	else if (this->m_pStateMachine->getCurrentState() == FleeingState::Instance() && distanceFromPlayer >= this->npc->getActionRange() * 2)
	{
		this->m_pStateMachine->changeState(WanderState::Instance());
	}
	this->m_pStateMachine->update(dt);
}

EvasiveBehaviour::~EvasiveBehaviour()
{
}
