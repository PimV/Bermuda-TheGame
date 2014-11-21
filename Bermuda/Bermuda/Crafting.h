#pragma once
#include "Inventory.h"
#include "Item.h"
#include "Items.h"

class Crafting
{
private:
	bool open;
	map<int, map<int, int>> recipes;
	void createRecipes();
public:
	Crafting();
	void init();
	bool canCraft(Inventory* inv, int itemID);
	Item* craftItem(Inventory* inv, int itemID);
	void draw();
	void toggleCraftMenu();
	void cleanup();
	virtual ~Crafting();
};