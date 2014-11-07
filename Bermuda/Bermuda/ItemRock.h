#pragma once
#include "item.h"
#include "Image.h"
enum class Items;

class ItemRock :
	public virtual Item
{
public:
	ItemRock(Image* image);

	void init(Image* image);

	virtual ~ItemRock();
};

