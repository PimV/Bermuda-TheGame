#include "Equipable.h"
#include "Player.h"
#include <iostream>


Equipable::Equipable(void)
{
}

void Equipable::equip(Player* player) {
	std::cout << "Equipping item with id: " << this->getId() << std::endl;
}

Equipable::~Equipable(void)
{
}