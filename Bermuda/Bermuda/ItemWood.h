#pragma once
#include "item.h"
#include "Image.h"
enum class Items;

class ItemWood :
	public virtual Item
{
public:
	ItemWood(Image* image);

	void init(Image* image);

	virtual ~ItemWood();
};

