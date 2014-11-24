#pragma once
#include "item.h"
#include "Consumable.h"
#include "Image.h"
enum class Items;

class ItemApple : 
	public virtual Consumable
{
public:
	ItemApple(Image* image);
		
	void init();
	void consume(Player* player);

	virtual ~ItemApple();
};

