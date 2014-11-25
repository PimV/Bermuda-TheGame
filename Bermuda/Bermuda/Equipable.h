#pragma once
#include "item.h"
class Player;
class Equipable :
	public  Item
{
public:
	Equipable(void);

	virtual void use(Player* p);

	virtual ~Equipable(void);
};

