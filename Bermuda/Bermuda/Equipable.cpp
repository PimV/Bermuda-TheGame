#include "Equipable.h"


Equipable::Equipable()
{
	this->setStackable(false);
}

void Equipable::use(Player* player) {
	player->getInventory()->selectStack(this);
}

Equipable::~Equipable()
{
}
