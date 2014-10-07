#include "MoveAction.h"


MoveAction::MoveAction(Player* p, EnumDirection direction)
{
	this->p = p;
	this->direction = direction;
}

void MoveAction::execute() {
	p->move(this->direction);
}

MoveAction::~MoveAction(void)
{
}
