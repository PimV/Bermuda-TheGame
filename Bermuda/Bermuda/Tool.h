#pragma once
#include "item.h"
class Player;
class Tool :
	public virtual Item
{
public:
	Tool(void);

	virtual void equip(Player* p);

	virtual ~Tool(void);
};

