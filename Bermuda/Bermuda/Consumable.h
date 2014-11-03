#pragma once
#include "item.h"
class Player;
class Consumable :
	public  Item
{
public:
	Consumable(void);

	virtual void consume(Player* p);
	void setHungerRefill(int hunger);
	void setThirstRefill(int thirst);
	void setHealthRefill(int health);
	int getHungerRefill();
	int getThirstRefill();
	int getHealthRefill();

	virtual ~Consumable(void);

private:
	int hungerRefill;
	int thirstRefill;
	int healthRefill;
};

