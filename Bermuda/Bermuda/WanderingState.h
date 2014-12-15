#pragma once
#include "IState.h"

class WanderingState :
	public IState
{
public:
	WanderingState();
	virtual ~WanderingState();

	void update(double dt);
};

