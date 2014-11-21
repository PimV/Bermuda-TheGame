#include "Crafting.h"
#include <iostream>



Crafting::Crafting()
{
	this->init();
}

void Crafting::init() 
{
	this->open = false;
	this->createRecipes();
}

void Crafting::createRecipes()
{
	this->recipes[(int)Items::Axe][(int)Items::Wood] = 3;
	this->recipes[(int)Items::Axe][(int)Items::Rock] = 3;
	this->recipes[(int)Items::Pickaxe][(int)Items::Wood] = 3;
	this->recipes[(int)Items::Pickaxe][(int)Items::Rock] = 3;
}

bool Crafting::canCraft(Inventory* inv, int itemID)
{
	map<int, map<int, int>>::iterator it = recipes.find(itemID);
	map<int, int> resources;
	if (it != recipes.end())
	{
		//recipe found;
		vector<Item*> reservedResources;
		map<int, int>::iterator iter;
		for (iter = resources.begin(); iter != resources.end(); ++iter) {
			int itemID = iter->first;
			int amount = iter->second;

			if (inv->hasItemById(itemID))
			{
				
			}
		}
	}
	else
	{
		//No recipe for this item.
		return false;
	}
}

Item* Crafting::craftItem(Inventory* inv, int itemID)
{
	if (canCraft(inv, itemID))
	{
		//Create item, remove resources from inventory
	}
}

void Crafting::toggleCraftMenu()
{
	open = !open;
}

void Crafting::cleanup()
{

}

Crafting::~Crafting()
{
	this->cleanup();
}
