#pragma once
#include "Consumable.h"
#include "Image.h"
#include "Player.h"

class ItemCarrot :
	public virtual Consumable
{
public:
	ItemCarrot(Image* image);

	void init();
	void consume(Player* player);

	virtual ~ItemCarrot();
};

