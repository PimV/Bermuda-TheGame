#include "BaseBehaviour.h"
#include <iostream>


BaseBehaviour::BaseBehaviour(StateMachine<Entity>* m_pStateMachine)
{
	this->npc = dynamic_cast<NPC*>( m_pStateMachine->getOwner() );
	this->m_pStateMachine = m_pStateMachine;
	this->m_pStateMachine->setCurrentState( WanderAround::Instance() );
}

void BaseBehaviour::update(double dt)
{
	this->m_pStateMachine->update(dt);
}

void BaseBehaviour::setFsmToDefaultState()
{
	this->m_pStateMachine->changeState( WanderAround::Instance() );
}

void BaseBehaviour::setFsmToActionState()
{
	this->m_pStateMachine->changeState( WanderAround::Instance() );
}

void BaseBehaviour::setFsmToAggressiveState()
{
	this->m_pStateMachine->changeState( AggressiveState::Instance() );
}

void BaseBehaviour::setFsmToDefenciveState()
{
	// TODO: set to defensiveState
}

void BaseBehaviour::setFsmToFleeingState()
{
	this->m_pStateMachine->changeState( FleeingState::Instance() );
}

void BaseBehaviour::setFsmToWanderState()
{
	this->m_pStateMachine->changeState( WanderAround::Instance() );
}

BaseBehaviour::~BaseBehaviour(void)
{
	delete this->m_pStateMachine;
	delete this->npc;
}
