#pragma once
#include "item.h"
#include "Player.h"
//class Player;

class Consumable :
	public  Item
{
public:
	Consumable(void);

	virtual void use(Player* p);
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

