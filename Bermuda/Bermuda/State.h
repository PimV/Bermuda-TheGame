#pragma once
#include "Entity.h"

class State
{
public:
	State();
	virtual ~State();

	virtual void Enter(Entity* entity) = 0;
	virtual void Execute(Entity* entity, double dt) = 0;
	virtual void Exit(Entity* entity) = 0;
};

