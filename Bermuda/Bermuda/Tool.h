#pragma once
#include "item.h"
#include "Equipable.h"
class Player;
class Tool :
	public Equipable
{
public:
	Tool(void);

	virtual void equip(Player* p);

	virtual ~Tool(void);
};

