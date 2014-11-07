#pragma once
#include "item.h"
#include "Consumable.h"
#include "Image.h"
enum class Items;

class ItemCarrot :
	public virtual Consumable
{
public:
	ItemCarrot(Image* image);

	void init(Image* image);
	void consume(Player* player);

	virtual ~ItemCarrot();
};

