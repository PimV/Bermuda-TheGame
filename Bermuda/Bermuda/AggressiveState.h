#pragma once
#include "State.h"

class AggressiveState :
	public State < Entity >
{
	private:
		AggressiveState(const AggressiveState &);
		AggressiveState& operator=(const AggressiveState &);

	protected:
		//

	public:
		AggressiveState();

		static AggressiveState* Instance();

		void enter(Entity* entity);
		void execute(Entity* entity, double dt);
		void exit(Entity* entity);

		virtual ~AggressiveState(void);
};
