#pragma once
#include "State.h"

class WanderAround :
	public State<Entity>
{
private:
	WanderAround(){};
	virtual ~WanderAround(){};

	WanderAround(const WanderAround &);
	WanderAround& operator=(const WanderAround &);
public:
	static WanderAround* Instance();

	void enter(Entity* entity);
	void execute(Entity* entity, double dt);
	void exit(Entity* entity);
};

