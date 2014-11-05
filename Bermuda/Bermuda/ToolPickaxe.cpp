#include "ToolPickaxe.h"
#include "Items.h"
#include <ctime>
#include <iostream>
#include "Player.h"

ToolPickaxe::ToolPickaxe() 
{
	init();
}

void ToolPickaxe::init() {
	this->setId((int)Items::Pickaxe);
	std::cout << "AXE ID: " << this->getId() << std::endl;
	this->setImage(GameStateManager::Instance()->getImageLoader()->getMapImage(GameStateManager::Instance()->getImageLoader()->loadTileset("Carrot.png", 30,22)));

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Tool);

	this->setMaxStackSize(1);

	int itemCount = 1;	
	this->setStackSize(itemCount);
}

void ToolPickaxe::equip(Player* player) {
	Equipable::equip(player);
}

ToolPickaxe::~ToolPickaxe(void)
{
}
