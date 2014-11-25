#include "Equipable.h"
#include "Player.h"
#include <iostream>


Equipable::Equipable(void)
{
}

void Equipable::use(Player* player) {
	player->getInventory()->selectStack(this);
}

Equipable::~Equipable(void)
{
}
