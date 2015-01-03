#include "BaseBehaviour.h"
#include <iostream>


BaseBehaviour::BaseBehaviour(StateMachine<Entity>* m_pStateMachine)
{
	this->m_pStateMachine = m_pStateMachine;
	this->npc = dynamic_cast<NPC*>( m_pStateMachine->getOwner() );
}

void BaseBehaviour::update(double dt)
{
		this->m_pStateMachine->update(dt);
}

void BaseBehaviour::setFsmToDefaultState()
{
	this->m_pStateMachine->changeState(WanderAround::Instance());
}

void BaseBehaviour::setFsmToActionState()
{
	this->m_pStateMachine->changeState(WanderAround::Instance());
}

void BaseBehaviour::setFsmToAggresdsiveState()
{
	std::cout << "NPC is now Aggressive \n";
	this->m_pStateMachine->changeState(AggressiveState::Instance());
}

void BaseBehaviour::setFsmToDefenciveState()
{
	// TODO: set to defensiveState
}

void BaseBehaviour::setFsmToFleeingState()
{
	// TODO: set to fleeingState
}

void BaseBehaviour::setFsmToWanderState()
{
	std::cout << "NPC is now Wandering \n";
	this->m_pStateMachine->changeState(WanderAround::Instance());
}

BaseBehaviour::~BaseBehaviour(void)
{
}
