#pragma once
#include "item.h"
#include "Tool.h"
enum class Items;
class ToolAxe :
	public Tool

{
public:
	ToolAxe();

	void init();
	void equip(Player* player);

	virtual ~ToolAxe(void);
};

