#include "Inventory.h"
#include <iostream>
#include "Items.h"
#include "Item.h"




Inventory::Inventory(void)
{
	this->init();

}

void Inventory::init() {
	std::cout<< "Created inv"<<std::endl;
	this->open = false;
	this->slots = 20;
	this->itemVector = std::vector<Item*>();
}

void Inventory::cleanup() {

}


bool Inventory::addItem(Item* item) {
	if (hasItem(item)) {
		//Tries to get an inventory slot with the existing item
		//Returns NULL if only full slots were found
		Item* inInvItem = this->getItemById(item->getId(), false);

		if (inInvItem == NULL) {
			if (this->getSize() <= slots) {
				//Can add item, inventory slots left
				std::cout << "Adding item in a new slot (all current slots filled)" << std::endl;
				this->itemVector.push_back(item);
			} else {
				//Could not add, no inventory slots left!
				std::cout << "Could not add into a new inventory slot, since the inventory was filled! (all slots filled)" << std::endl;
			}
		} else {
			//Try to up stacksize of an existing inventory slot
			while (item->getStackSize() > 0) {
				//	std::cout << "Item to add stacksize: " << item->getStackSize() << std::endl;
				if (inInvItem->getStackSize() >= inInvItem->getMaxStackSize()) {
					this->itemVector.push_back(item);
					break;
				} else {
					inInvItem->setStackSize(inInvItem->getStackSize() + 1);
					item->setStackSize(item->getStackSize() - 1);
				}
			}
		}
	} else {
		if (this->getSize() <= this->slots) {
			this->itemVector.push_back(item);
		} else {
			//No inventory slots left;
		}
	}
	return true;
}

Item* Inventory::getItemById(int id, bool full) {
	for (size_t i = 0; i < this->itemVector.size(); i++) {
		if (this->itemVector[i]->getId() == id) {
			if (!full) {
				if (this->itemVector[i]->getStackSize() < this->itemVector[i]->getMaxStackSize()) {
					return this->itemVector[i];
				}
			} else {
				return this->itemVector[i];
			}
		}
	}
	return NULL;
}

bool Inventory::hasItem(Item* item) {
	for (size_t i = 0; i < this->itemVector.size(); i++) {
		if (this->itemVector[i] != NULL && this->itemVector[i]->getId() == item->getId()) {
			return true;
		}
	}
	return false;
}

bool Inventory::hasItemById(int itemId) {
	for (size_t i = 0; i < this->itemVector.size(); i++) {
		if (this->itemVector[i] != NULL && this->itemVector[i]->getId() == itemId) {
			return true;
		}
	}
	return false;
}
void Inventory::deleteItem(Item* item, int count) {

	item->setStackSize(item->getStackSize() - count);

	if (item->getStackSize() == 0) {
		std::vector<Item*>::iterator it = std::find(this->itemVector.begin(), this->itemVector.end(), item);
		this->itemVector.erase(it);
	}


}

bool Inventory::hasAxe() {
	return this->hasItemById((int)Items::Axe);
}

bool Inventory::hasPickaxe() {
	return this->hasItemById((int)Items::Pickaxe);
}

std::vector<Item*> Inventory::getItems() {
	return this->itemVector;
}

int Inventory::getSize() {
	return this->itemVector.size();
}


void Inventory::printInventory() {
	std::cout << "INVENTORY: " << std::endl;
	for (size_t i = 0; i < 20; i++) {
		/*if (i % 4 == 0) {
		std::cout <<  std::endl;
		}*/

		if (i < this->getSize()) {
			std::cout << "[" << item_strings[this->itemVector[i]->getId()] << ": " <<  this->itemVector[i]->getStackSize() << "] ";
		} else {
			std::cout << "[ ] ";
		}
		std::cout << std::endl;
	}
	std::cout <<std::endl;
}

bool Inventory::isOpen() {
	return this->open;
}
void Inventory::toggleInventory() {
	this->open = !this->open;
}

void Inventory::draw() {
	int y = 50;
	for (size_t i = 0; i < 20; i++) {
		if (i < this->getSize()) {
			GameStateManager::Instance()->sdlInitializer->drawText(
				std::string(item_strings[this->itemVector[i]->getId()] + std::string(":") + std::to_string(this->itemVector[i]->getStackSize())), 20, 16*i + 5,100, 16
				);
		}
	}

}


Inventory::~Inventory(void)
{
}
