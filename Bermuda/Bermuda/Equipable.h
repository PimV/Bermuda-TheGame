#pragma once
#include "item.h"
#include "Player.h"

class Equipable :
	public Item
{
public:
	Equipable();

	virtual void use(Player* p);

	virtual ~Equipable();
};

