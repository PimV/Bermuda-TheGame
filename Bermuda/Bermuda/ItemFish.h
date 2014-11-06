#pragma once
#include "item.h"
#include "Consumable.h"
enum class Items;


class ItemFish :
	public virtual Consumable
{
public:
	ItemFish();
	
	void init();
	void consume(Player* player);

	virtual ~ItemFish();
};

