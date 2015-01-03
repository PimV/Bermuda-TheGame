#pragma once
#include "BaseBehaviour.h"
#include "AggressiveState.h"

class Aggressive :
	public BaseBehaviour
{
	private:
		void executeAction();

	protected:
		//

	public:
		Aggressive(StateMachine<Entity>* m_pStateMachine);
	
		void update(double dt);

		virtual ~Aggressive(void);	
};
