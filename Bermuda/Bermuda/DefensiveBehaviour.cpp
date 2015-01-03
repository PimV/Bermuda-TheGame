#include "DefensiveBehaviour.h"
#include <iostream>

DefensiveBehaviour::DefensiveBehaviour(StateMachine<Entity>* m_pStateMachine) : 
	BaseBehaviour(m_pStateMachine)
{
}

void DefensiveBehaviour::executeAction()
{
	std::cout << "NPC is now Defending object \n";
}

void DefensiveBehaviour::update(double dt)
{
}

DefensiveBehaviour::~DefensiveBehaviour(void)
{
}
