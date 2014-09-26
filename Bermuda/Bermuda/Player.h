#pragma once
#include "entity.h"
#include "IMovable.h"

class Player :
	public Entity,
	public IMovable
{
public:
	Player(int id, double moveSpeed);
	virtual void move();
	~Player(void);
};

