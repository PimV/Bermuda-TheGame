#pragma once
#include "BaseBehaviour.h"
class EvasiveBehaviour :
	public BaseBehaviour
{
	private:
		void executeAction();

	protected:
		//

	public:
		EvasiveBehaviour(StateMachine<Entity>* m_pStateMachine);

		void update(double dt);

		virtual ~EvasiveBehaviour(void);
};

