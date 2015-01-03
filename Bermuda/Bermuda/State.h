#pragma once
//#include "Entity.h"
class Entity;

template <class entity_type>
class State
{

protected:
	int actionRange, attackRange;
	Entity *entity;

public:
	virtual ~State(){};

	virtual void enter(entity_type*) = 0;
	virtual void execute(entity_type*, double dt) = 0;
	virtual void exit(entity_type*) = 0;
};
