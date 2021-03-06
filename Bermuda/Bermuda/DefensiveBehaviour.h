#pragma once
#include "BaseBehaviour.h"
#include "AttackingNPC.h"

class DefensiveBehaviour :
	public BaseBehaviour
{
	private:
		void executeAction();

	public:
		DefensiveBehaviour(StateMachine<Entity>* m_pStateMachine);

		void update(double dt);

		virtual ~DefensiveBehaviour();
};

