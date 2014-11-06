#include "MoveAction.h"


MoveAction::MoveAction(Player* p, EnumDirection direction)
{
	this->p = p;
	this->direction = direction;
}

void MoveAction::execute(double dt) {
	p->walk(dt);
}

MoveAction::~MoveAction(void)
{
}
