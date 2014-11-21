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
	this->recipes[Items::Axe][Items::Wood] = 3;
	this->recipes[Items::Axe][Items::Rock] = 3;
	this->recipes[Items::Pickaxe][Items::Wood] = 3;
	this->recipes[Items::Pickaxe][Items::Rock] = 3;
}

bool Crafting::canCraft(Items item)
{
	map<Items, map<Items, int>>::iterator it = recipes.find(item);
	map<Items, int> resources;
	if (it != recipes.end())
	{
		//recipe found;
		resources = recipes[item];
		bool canCraft = true;
		vector<Item*> reservedResources;
		for (pair<Items, int> pair : resources)
		{
			int itemID = (int)pair.first;
			int amount = pair.second;

			if (this->inventory->hasItemById(itemID) && this->inventory->getItemById(itemID, true)->getStackSize() >= amount)
			{
				//Remove the item from player inventory to check if slots become available after removal.
				Item* item = this->inventory->getItemById(itemID, true);
				item->setStackSize(amount);
				reservedResources.push_back(item);
				this->inventory->deleteItem(item, amount);
			}
			else
			{
				//Item not in inventory. 
				canCraft = false;
				break;
			}
		}

		//If it is still possible to craft the item, check if there is an inventory slot available.
		if (canCraft && !(this->inventory->getSize() < this->inventory->getSlots()))
		{
			canCraft = false;
		}

		//Return all resources. 
		for (Item* item : reservedResources)
		{
			this->inventory->addItem(item);
		}

		return canCraft;
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
			this->inventory->deleteItem(this->inventory->getItemById(itemID, true), amount);
		}

		//Create item
		this->inventory->addItem(ItemFactory::Instance()->createItem(item));

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
