#include "ToolGoldenAxe.h"


ToolGoldenAxe::ToolGoldenAxe(Image* image) 
{
	this->setImage(image);
	init();
}

void ToolGoldenAxe::init() {
	this->setId((int)Items::GoldenAxe);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::WorkTool);

	this->setMaxStackSize(1);

	int itemCount = 1;	
	this->setStackSize(itemCount);

	this->setMaxDurability(30);
	this->setDurability(30);
}

ToolGoldenAxe::~ToolGoldenAxe()
{
}
