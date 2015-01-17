#pragma once
#include "BaseBehaviour.h"
#include "PlayState.h"

class EvasiveBehaviour :
	public BaseBehaviour
{
	private:
		void executeAction();

	public:
		EvasiveBehaviour(StateMachine<Entity>* m_pStateMachine);

		void update(double dt);

		virtual ~EvasiveBehaviour();
};
