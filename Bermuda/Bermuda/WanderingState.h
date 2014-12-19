#pragma once
#include "State.h"
#include "MovableEntity.h"
#include "NPC.h"

class WanderingState :
	public State
{
public:
	WanderingState(Entity* entity);
	virtual ~WanderingState();

	void execute(double dt);
private:
	MovableEntity* movableEntity;
	NPC* npc;
};

