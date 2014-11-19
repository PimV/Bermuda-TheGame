#pragma once
#include "item.h"
#include "Consumable.h"
#include "Image.h"
enum class Items;

class ItemWater :
	public virtual Consumable
{
public:
	ItemWater(Image* image);

	void init();
	void consume(Player* player);

	virtual ~ItemWater();
};

