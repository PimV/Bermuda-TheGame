#pragma once
#include "Entity.h"

class State
{
public:
	State();
	virtual ~State();

	virtual void enter(Entity* entity) = 0;
	virtual void execute(Entity* entity, double dt) = 0;
	virtual void exit(Entity* entity) = 0;
};

