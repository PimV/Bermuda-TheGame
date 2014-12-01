#pragma once
#include "Consumable.h"
#include "Image.h"
#include "Player.h"

class ItemApple : 
	public virtual Consumable
{
public:
	ItemApple(Image* image);
		
	void init();
	void consume(Player* player);

	virtual ~ItemApple();
};

