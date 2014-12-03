#include "Crafting.h"
#include "ItemFactory.h"
#include <iostream>



Crafting::Crafting(Inventory* inv)
{
	this->init(inv);
}

void Crafting::init(Inventory* inv)
{
	//TODO: add to GUI container
	this->open = false;
	this->inventory = inv;
	this->createRecipes();
}

void Crafting::createRecipes()
{
	this->recipes[Items::Axe][Items::Wood] = 2;
	this->recipes[Items::Axe][Items::Rock] = 2;
	this->recipes[Items::Pickaxe][Items::Wood] = 2;
	this->recipes[Items::Pickaxe][Items::Rock] = 2;
	this->recipes[Items::Campfire][Items::Wood] = 3;
	this->recipes[Items::Campfire][Items::Rock] = 3;
}

bool Crafting::canCraft(Items item)
{
	map<Items, map<Items, int>>::iterator it = recipes.find(item);
	map<Items, int> resources;
	if (it != recipes.end())
	{
		//recipe found;
		resources = recipes[item];
		int slotsFreedByCrafting = 0;
		for (pair<Items, int> pair : resources)
		{
			int itemID = (int)pair.first;
			int amount = pair.second;

			//Check if enough resources are in the inventory.
			if (this->inventory->getItemCount(itemID) >= amount)
			{
				slotsFreedByCrafting += this->inventory->getSlotsFreedWhenDeleting(itemID, amount);
			}
			else
			{
				return false;
			}
		}

		//Enough resources are available. Check if a slot is available after crafting.
		if (this->inventory->getSize() - slotsFreedByCrafting < this->inventory->getSlots())
		{
			return true;
		}
	}
	else
	{
		//No recipe for this item.
		return false;
	}
}

void Crafting::craftItem(Items item)
{
	if (canCraft(item))
	{
		//Remove resources from inventory
		for (pair<Items, int> pair : recipes[item])
		{
			int itemID = (int)pair.first;
			int amount = pair.second;
			this->inventory->deleteItem(itemID, amount);
		}

		//Create item
		this->inventory->addItem(ItemFactory::Instance()->createItem(item));

	}
}

void Crafting::toggleCraftMenu()
{
	open = !open;
}

void Crafting::draw()
{

}

void Crafting::cleanup()
{

}

Crafting::~Crafting()
{
	this->cleanup();
}
