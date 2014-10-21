#include "Item.h"

Item::Item(int id, int maxStackSize, bool stackable, Image* image) :
	id(id), maxStackSize(maxStackSize), stackable(stackable), image(image)
{
	this->init();
}

void Item::init() {
	this->itemTypes = std::vector<ItemType*>();
	this->stackSize = 1;
}

void Item::cleanup() {

}

int Item::getId() {
	return this->id;
}

int Item::getStackSize() {
	return this->stackSize;
}

int Item::getMaxStackSize() {
	return this->maxStackSize;
}

void Item::setStackSize(int size) {
	this->stackSize = size;
	if (this->stackSize < 0) {
		this->stackSize = 0;
	}
	if (this->stackSize > 0) {
		if (stackable == false) {
			this->stackSize = 1;
		}
	}


}

void Item::addItemType(ItemType* itemType) {
	//Get iterator for value
	std::vector<ItemType*>::iterator it = std::find(this->itemTypes.begin(), this->itemTypes.end(), itemType);
	//If iterator is equal to the 'ends' iterator, item is not found
	if(it == this->itemTypes.end()) {
		this->itemTypes.push_back(itemType);
	}
}

bool Item::hasItemType(ItemType* itemType) {
	std::vector<ItemType*>::iterator it = std::find(this->itemTypes.begin(), this->itemTypes.end(), itemType);
	if (it != this->itemTypes.end()) {
		return true;
	}
	return false;
}

void Item::removeItemType(ItemType* itemType) {
	//Get iterator for value
	std::vector<ItemType*>::iterator it = std::find(this->itemTypes.begin(), this->itemTypes.end(), itemType);
	//If iterator is not equal to the 'ends' iterator, item is found
	if(it != this->itemTypes.end()) {
		this->itemTypes.erase(it);
	}
}

std::vector<ItemType*> Item::getItemTypes() {
	return this->itemTypes;
}

bool Item::getStackable() {
	return this->stackable;
}


Item::~Item(void)
{

}
