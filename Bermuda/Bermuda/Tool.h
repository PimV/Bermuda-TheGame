#pragma once
#include "Equipable.h"
#include "Player.h"

class Tool :
	public Equipable
{
public:
	Tool(void);

	void setDurability(int durability);
	int getDurability();

	virtual ~Tool(void);
private:
	int durability;
};

