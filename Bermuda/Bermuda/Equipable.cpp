#include "Equipable.h"


Equipable::Equipable()
{
}

void Equipable::use(Player* player) {
	player->getInventory()->selectStack(this);
}

Equipable::~Equipable()
{
}
