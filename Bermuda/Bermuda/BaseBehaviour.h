#pragma once
#include "StateMachine.h"
#include "WanderState.h"
#include "AggressiveState.h"
#include "FleeingState.h"
#include "InteractableNPC.h"

class BaseBehaviour
{
	private:
		//

	protected:
		StateMachine<Entity>* m_pStateMachine;
		InteractableNPC* npc;

		virtual void executeAction() = 0;

	public:
		BaseBehaviour(StateMachine<Entity>* m_pStateMachine);

		virtual void update(double dt) = 0;
		virtual void setFsmToDefaultState();
		virtual void setFsmToActionState();

		virtual void setFsmToAggressiveState();
		virtual void setFsmToDefenciveState();
		virtual void setFsmToFleeingState();
		virtual void setFsmToWanderState();

		virtual ~BaseBehaviour(void);
};
