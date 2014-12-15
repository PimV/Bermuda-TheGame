#pragma once
#include "IState.h"
#include "MovableEntity.h"
#include "NPC.h"

class WanderingState :
	public IState
{
public:
	WanderingState(Entity* entity);
	virtual ~WanderingState();

	void update(double dt);
private:
	MovableEntity* movableEntity;
	NPC* npc;
};

