#pragma once
#include "Inventory.h"
#include "Items.h"
#include <map>

class Crafting
{
private:
	bool open;
	Inventory* inventory;
	std::map<Items, std::map<Items, int>> recipes;
	void createRecipes();
public:
	Crafting(Inventory* inv);
	void init(Inventory* inv);
	bool canCraft(Items item);
	void craftItem(Items item);
	void draw();
	void toggleCraftMenu();
	void cleanup();
	virtual ~Crafting();
};