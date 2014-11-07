#include "ToolAxe.h"
#include "Items.h"
#include <ctime>
#include <iostream>
#include "Player.h"

ToolAxe::ToolAxe(Image* image) 
{
	init(image);
}

void ToolAxe::init(Image* image) {
	this->setId((int)Items::Axe);
	std::cout << "AXE ID: " << this->getId() << std::endl;
	this->setImage(GameStateManager::Instance()->getImageLoader()->getMapImage(GameStateManager::Instance()->getImageLoader()->loadTileset("Carrot.png", 30,22)));

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Tool);

	this->setMaxStackSize(1);

	int itemCount = 1;	
	this->setStackSize(itemCount);
}

void ToolAxe::equip(Player* player) {
	Equipable::equip(player);
}

ToolAxe::~ToolAxe()
{
}
