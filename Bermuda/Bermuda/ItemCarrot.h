#pragma once
#include "item.h"
#include "Consumable.h"
enum class Items;
class ItemCarrot :
	public virtual Consumable
{
public:
	ItemCarrot();

	void init();
	void consume(Player* player);

	virtual ~ItemCarrot(void);
};

