#include "ToolGoldenAxe.h"


ToolGoldenAxe::ToolGoldenAxe(Image* image) 
{
	this->setImage(image);
	init();
}

void ToolGoldenAxe::init() {
	this->setId((int)Items::GoldenAxe);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Tool);

	this->setMaxStackSize(1);

	int itemCount = 1;	
	this->setStackSize(itemCount);
}

ToolGoldenAxe::~ToolGoldenAxe()
{
}
