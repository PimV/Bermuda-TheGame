#pragma once
#include "Consumable.h"
#include "Image.h"
#include "Player.h"

class ItemFish :
	public virtual Consumable
{
public:
	ItemFish(Image* image);
	
	void init();
	void consume(Player* player);

	virtual ~ItemFish();
};

