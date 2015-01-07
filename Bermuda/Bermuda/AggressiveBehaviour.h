#pragma once
#include "BaseBehaviour.h"
#include "AggressiveState.h"
#include "AttackingNPC.h"

class AggressiveBehaviour :
	public BaseBehaviour
{
	private:
		void executeAction();

	public:
		AggressiveBehaviour(StateMachine<Entity>* m_pStateMachine);
	
		void update(double dt);

		virtual ~AggressiveBehaviour(void);	
};
