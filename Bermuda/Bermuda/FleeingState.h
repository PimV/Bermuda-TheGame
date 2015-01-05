#pragma once
#include "State.h"


class FleeingState :
	public State < Entity >
{
private:
	FleeingState();

	FleeingState(const FleeingState &);
	FleeingState& operator=(const FleeingState &);

	virtual ~FleeingState();
public:
	static FleeingState* Instance();

	void enter(Entity* entity);
	void execute(Entity* entity, double dt);
	void exit(Entity* entity);
};

