#include "EvasiveBehaviour.h"
#include <iostream>

EvasiveBehaviour::EvasiveBehaviour(StateMachine<Entity>* m_pStateMachine) : 
	BaseBehaviour(m_pStateMachine)
{

}

void EvasiveBehaviour::executeAction()
{
	// might not ne needed here
}

void EvasiveBehaviour::update(double dt)
{
	this->m_pStateMachine->update(dt);
}

EvasiveBehaviour::~EvasiveBehaviour(void)
{
	delete m_pStateMachine;
}
