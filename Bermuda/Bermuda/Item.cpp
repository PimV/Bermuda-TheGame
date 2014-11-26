#include "Item.h"
#include "Image.h"
#include "Items.h"
#include <iostream>

Item::Item()
{
	this->init();
}

void Item::init() {
	this->itemTypes = std::vector<ItemType>();
	this->stackSize = 1;
}

void Item::cleanup() {

}

int Item::getId() {
	return this->id;
}

void Item::setId(int id) {
	this->id = id;
}

int Item::getStackSize() {
	return this->stackSize;
}

void Item::setStackSize(int size) {
	this->stackSize = size;
	if (this->stackSize > 0) {
		if (stackable == false) {
			this->stackSize = 1;
		}
	}
}

int Item::getMaxStackSize() {
	return this->maxStackSize;
}

void Item::setMaxStackSize(int maxStackSize) {
	this->maxStackSize = maxStackSize;
}

bool Item::getStackable() {
	return this->stackable;
}

void Item::setStackable(bool stackable) {
	this->stackable = stackable;
}

Image* Item::getImage() {
	return this->image;
}

void Item::setImage(Image* image) {
	this->image = image;
}

void Item::use(Player* p){}

void Item::addItemType(ItemType itemType) {
	//Get iterator for value
	std::vector<ItemType>::iterator it = std::find(this->itemTypes.begin(), this->itemTypes.end(), itemType);
	//If iterator is equal to the 'ends' iterator, item is not found
	if(it == this->itemTypes.end()) {
		this->itemTypes.push_back(itemType);
	}
}

bool Item::hasItemType(ItemType itemType) {
	std::vector<ItemType>::iterator it = std::find(this->itemTypes.begin(), this->itemTypes.end(), itemType);
	if (it != this->itemTypes.end()) {
		return true;
	}
	return false;
}

void Item::removeItemType(ItemType itemType) {
	//Get iterator for value
	std::vector<ItemType>::iterator it = std::find(this->itemTypes.begin(), this->itemTypes.end(), itemType);
	//If iterator is not equal to the 'ends' iterator, item is found
	if(it != this->itemTypes.end()) {
		this->itemTypes.erase(it);
	}
}

std::vector<ItemType> Item::getItemTypes() {
	return this->itemTypes;
}

bool Item::isConsumable() {
	return this->hasItemType(ItemType::Drink) || this->hasItemType(ItemType::Food);
}

bool Item::isEquipable() {
	return this->hasItemType(ItemType::Armour) || this->hasItemType(ItemType::Tool) || this->hasItemType(ItemType::Weapon);
}

Item::~Item(void)
{
}
