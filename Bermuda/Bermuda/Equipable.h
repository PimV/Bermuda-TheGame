#pragma once
#include "item.h"
class Player;
class Equipable :
	public  Item
{
public:
	Equipable(void);

	virtual void equip(Player* p);

	virtual ~Equipable(void);
};

