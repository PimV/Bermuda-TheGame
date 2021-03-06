#include "Consumable.h"
#include <iostream>


Consumable::Consumable()
{
}

void Consumable::use(Player* player) {
	if (player->getInventory()->hasItemById(this->getId())) {
		player->setHunger(player->getHunger() + this->getHungerRefill());
		player->setThirst(player->getThirst() + this->getThirstRefill());
		player->setHealth(player->getHealth() + this->getHealthRefill());

		//player->getInventory()->deleteItem(player->getInventory()->getItemById(this->getId(), true), 1);
		player->getInventory()->deleteItemFromStack(this, 1);

	} else {
		std::cout << "Item not in inventory" << std::endl;
	}

}

void Consumable::setHealthRefill(int health) {
	this->healthRefill = health;
}

void Consumable::setHungerRefill(int hunger) {
	this->hungerRefill = hunger;
}

void Consumable::setThirstRefill(int thirst) {
	this->thirstRefill = thirst;
}

int Consumable::getHealthRefill() {
	return this->healthRefill;
}

int Consumable::getThirstRefill() {
	return this->thirstRefill;
}
int Consumable::getHungerRefill() {
	return this->hungerRefill;
}
Consumable::~Consumable()
{
}
