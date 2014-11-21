#include "Crafting.h"
#include "ItemFactory.h"
#include <iostream>



Crafting::Crafting()
{
	this->init();
}

void Crafting::init() 
{
	//TODO: add to GUI container
	this->open = false;
	this->createRecipes();
}

void Crafting::createRecipes()
{
	this->recipes[Items::Axe][Items::Wood] = 3;
	this->recipes[Items::Axe][Items::Rock] = 3;
	this->recipes[Items::Pickaxe][Items::Wood] = 3;
	this->recipes[Items::Pickaxe][Items::Rock] = 3;
}

bool Crafting::canCraft(Inventory* inv, Items item)
{
	map<Items, map<Items, int>>::iterator it = recipes.find(item);
	map<Items, int> resources;
	if (it != recipes.end())
	{
		//recipe found;
		bool canCraft;
		vector<Item*> reservedResources;
		for (pair<Items, int> pair : resources)
		{
			int itemID = (int)pair.first;
			int amount = pair.second;

			if (inv->hasItemById(itemID) && inv->getItemById(itemID, true)->getStackSize() >= amount)
			{
				//Remove the item from player inventory to check if slots become available after removal.
				Item* item = inv->getItemById(itemID, true);
				item->setStackSize(amount);
				inv->deleteItem(item, amount);
			}
			else
			{
				//Item not in inventory. 
				canCraft = false;
				break;
			}
		}

		//If it is still possible to craft the item, check if there is an inventory slot available.
		if (canCraft && !(inv->getSize() < inv->getSlots()))
		{
			canCraft = false;
		}

		//Return all resources. 
		for (Item* item : reservedResources)
		{
			inv->addItem(item);
		}

		return canCraft;
	}
	else
	{
		//No recipe for this item.
		return false;
	}
}

void Crafting::craftItem(Inventory* inv, Items item)
{
	if (canCraft(inv, item))
	{
		//Remove resources from inventory
		for (pair<Items, int> pair : recipes[item])
		{
			int itemID = (int)pair.first;
			int amount = pair.second;
			inv->deleteItem(inv->getItemById(itemID, true), amount);
		}

		//Create item
		inv->addItem(ItemFactory::Instance()->createItem(item));

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
