#pragma once
#include "item.h"
#include "Tool.h"
enum class Items;
class ToolPickaxe :
	public Tool
{
public:
	ToolPickaxe();

	void init();
	void equip(Player* player);

	virtual ~ToolPickaxe(void);
};

