#include "BaseBehaviour.h"

BaseBehaviour::BaseBehaviour(StateMachine<Entity>* m_pStateMachine)
{
	this->npc = dynamic_cast<InteractableNPC*>( m_pStateMachine->getOwner() );
	this->m_pStateMachine = m_pStateMachine;

	this->m_pStateMachine->setCurrentState( WanderState::Instance() );
}

void BaseBehaviour::update(double dt)
{
	this->m_pStateMachine->update(dt);
}

void BaseBehaviour::setFsmToDefaultState()
{
	this->m_pStateMachine->changeState( WanderState::Instance() );
}

void BaseBehaviour::setFsmToActionState()
{
	this->m_pStateMachine->changeState( WanderState::Instance() );
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
	this->m_pStateMachine->changeState( WanderState::Instance() );
}

BaseBehaviour::~BaseBehaviour(void)
{
	delete this->m_pStateMachine;
	delete this->npc;
}
