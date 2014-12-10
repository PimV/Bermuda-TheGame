#pragma once
#include "item.h"
#include "Player.h"

class Equipable :
	public Item
{
public:
	Equipable();

	virtual void use(Player* p);

	void setMaxDurability(int maxDurability);
	int getMaxDurability();

	void setDurability(int durability);
	int getDurability();

	int getPercentageDegraded();

	virtual ~Equipable();
private:
	int durability;
	int maxDurability;
	double percentageDegraded;
};

