#pragma once
#include "item.h"
#include "Consumable.h"
#include "Image.h"
enum class Items;


class ItemFish :
	public virtual Consumable
{
public:
	ItemFish(Image* image);
	
	void init(Image* image);
	void consume(Player* player);

	virtual ~ItemFish();
};

