#pragma once
#include "Consumable.h"
#include "Image.h"
#include "Player.h"

class ItemMeat :
	public virtual Consumable
{
public:
	ItemMeat(Image* image);

	void init();
	void consume(Player* player);

	virtual ~ItemMeat();
};

