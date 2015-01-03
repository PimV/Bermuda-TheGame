#include "EvasiveBehaviour.h"
#include <iostream>

EvasiveBehaviour::EvasiveBehaviour(StateMachine<Entity>* m_pStateMachine) : 
	BaseBehaviour(m_pStateMachine)
{

}

void EvasiveBehaviour::executeAction()
{
	std::cout << "NPC is now Evading Player \n";
}

void EvasiveBehaviour::update(double dt)
{
}

EvasiveBehaviour::~EvasiveBehaviour(void)
{

}
