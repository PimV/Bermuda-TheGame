#include "Equipable.h"


Equipable::Equipable()
{
	this->setStackable(false);
	this->durability = -1;
	this->maxDurability = -1;
	this->percentageDegraded = 100;
}

void Equipable::use(Player* player) {
	player->getInventory()->selectStack(this);
}

void Equipable::setMaxDurability(int maxDurability) {
	this->maxDurability = maxDurability;
}

int Equipable::getMaxDurability() {
	return this->maxDurability;
}

void Equipable::setDurability(int durability) {
	this->durability = durability;
	//casten voor percentages
	this->percentageDegraded = 100 - (static_cast<double>(this->durability) / static_cast<double>(this->maxDurability))*100;

}

int Equipable::getDurability() {
	return this->durability;
}

int Equipable::getPercentageDegraded() {
	return static_cast<int>(ceil(this->percentageDegraded));
}

Equipable::~Equipable()
{
}
