#pragma once
#include "item.h"
enum class Items;
class ItemWood :
	public virtual Item
{
public:
	ItemWood(void);

	void init();

	virtual ~ItemWood(void);
};

