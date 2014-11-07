#pragma once
#include "item.h"
#include "Tool.h"
#include "Image.h"
enum class Items;

class ToolPickaxe :
	public Tool
{
public:
	ToolPickaxe(Image* image);

	void init(Image* image);
	void equip(Player* player);

	virtual ~ToolPickaxe();
};

