#pragma once
#include "Consumable.h"
#include "Image.h"
#include "Player.h"

class ItemWater :
	public virtual Consumable
{
public:
	ItemWater(Image* image);

	void init();
	void consume(Player* player);

	virtual ~ItemWater();
};

