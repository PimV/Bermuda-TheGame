#pragma once
#include "item.h"
enum class Items;
class ItemRock :
	public virtual Item
{
public:
	ItemRock(void);

	void init();

	virtual ~ItemRock(void);
};

