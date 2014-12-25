#include "ToolGoldenPickaxe.h"


ToolGoldenPickaxe::ToolGoldenPickaxe(Image* image) 
{
	this->setImage(image);
	init();
}

void ToolGoldenPickaxe::init() {
	this->setId((int)Items::GoldenPickaxe);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::WorkTool);

	this->setMaxStackSize(1);

	int itemCount = 1;	
	this->setStackSize(itemCount);

	this->setMaxDurability(30);
	this->setDurability(30);
}


ToolGoldenPickaxe::~ToolGoldenPickaxe()
{
}
