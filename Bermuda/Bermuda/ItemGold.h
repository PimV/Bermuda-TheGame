#pragma once
#include "item.h"
#include "Image.h"
enum class Items;

class ItemGold :
	public virtual Item
{
public:
	ItemGold(Image* image);

	void init();

	virtual ~ItemGold();
};

