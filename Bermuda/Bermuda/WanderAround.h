#pragma once
#include "State.h"
#include "MovableEntity.h"
#include "NPC.h"

class WanderAround :
	public State
{
private:
	WanderAround(){}

	WanderAround(const WanderAround &);
	WanderAround& operator=(const WanderAround &);
public:
	virtual ~WanderAround();
	static WanderAround* Instance();

	void Enter(Entity* entity);
	void Execute(Entity* entity, double dt);
	void Exit(Entity* entity);
};

