#pragma once
#include "Inventory.h"
#include "Items.h"
#include <map>

class Crafting
{
private:
	bool open;
	std::map<Items, std::map<Items, int>> recipes;
	void createRecipes();
public:
	Crafting();
	void init();
	bool canCraft(Inventory* inv, Items item);
	void craftItem(Inventory* inv, Items item);
	void draw();
	void toggleCraftMenu();
	void cleanup();
	virtual ~Crafting();
};