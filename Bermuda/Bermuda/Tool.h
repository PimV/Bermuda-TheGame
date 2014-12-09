#pragma once
#include "Equipable.h"
#include "Player.h"

class Tool :
	public Equipable
{
public:
	Tool(void);

	void setMaxDurability(int maxDurability);
	int getMaxDurability();

	void setDurability(int durability);
	int getDurability();

	int getPercentageDegraded();

	virtual ~Tool(void);
private:
	int durability;
	int maxDurability;
	double percentageDegraded;
};

