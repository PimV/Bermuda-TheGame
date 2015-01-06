#pragma once
#include "State.h"
#include "MovableEntity.h"
#include "NPC.h"
#include "GameTimer.h"
#include <time.h>
#include <random>
#include <assert.h>

class WanderState :
	public State<Entity>
{
private:
	WanderState(){};
	virtual ~WanderState(){};

	WanderState(const WanderState &);
	WanderState& operator=(const WanderState &);

public:
	static WanderState* Instance();

	void enter(Entity* entity);
	void execute(Entity* entity, double dt);
	void exit(Entity* entity);
};
