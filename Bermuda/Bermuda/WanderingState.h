#pragma once
#include "State.h"
#include "MovableEntity.h"
#include "NPC.h"

class WanderingState :
	public State
{
public:
	WanderingState();
	virtual ~WanderingState();
	
	void enter(Entity* entity);
	void execute(Entity* entity, double dt);
	void exit(Entity* entity);
private:
	MovableEntity* movableEntity;
	NPC* npc;
};

