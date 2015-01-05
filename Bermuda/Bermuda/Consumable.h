#pragma once
#include "item.h"
#include "Player.h"

class Consumable :
	public  Item
{
public:
	Consumable();

	virtual void use(Player* p);
	void setHungerRefill(int hunger);
	void setThirstRefill(int thirst);
	void setHealthRefill(int health);
	int getHungerRefill();
	int getThirstRefill();
	int getHealthRefill();

	virtual ~Consumable();

private:
	int hungerRefill;
	int thirstRefill;
	int healthRefill;
};

