#pragma once
#include "item.h"
enum class Items;
class ItemCarrot :
	public virtual Item
{
public:
	ItemCarrot();

	void init();

	virtual ~ItemCarrot(void);
};

