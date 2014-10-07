#pragma once
#include "entity.h"
#include "IMovable.h"


class Player :
	public Entity,
	public IMovable
{
public:
	Player(int id, double moveSpeed);
	//virtual void move(EnumDirection direction) = 0;
	virtual void move(EnumDirection direction);// = 0;
	~Player(void);
};

