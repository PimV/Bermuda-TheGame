#pragma once
#include "item.h"
#include "Image.h"

class ItemGold :
	public virtual Item
{
public:
	ItemGold(Image* image);

	void init();

	virtual ~ItemGold();
};

