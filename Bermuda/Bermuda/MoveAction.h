#pragma once
#include "iaction.h"
#include "Player.h"
#include "EnumDirection.h"
class MoveAction :
	public IAction
{
public:
	MoveAction(Player* p, EnumDirection direction);

	void execute(double dt);

	virtual ~MoveAction(void);
private:
	Player* p;
	EnumDirection direction;
};

