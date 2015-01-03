#pragma once
#include "BaseBehaviour.h"
class DefensiveBehaviour :
	public BaseBehaviour
{
	private:
		void executeAction();

	protected:
		//

	public:
		DefensiveBehaviour(StateMachine<Entity>* m_pStateMachine);

		void update(double dt);

		virtual ~DefensiveBehaviour(void);
};

