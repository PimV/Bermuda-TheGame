#include "Inventory.h"
#include "Items.h"
#include "Item.h"
#include "Image.h"
#include "Consumable.h"
#include "Equipable.h"
#include "Player.h"
#include <iostream>
#include <algorithm>


//Needed for vector sort
bool Inventory::stackSortFunction(Item* one, Item* two) { return (one->getStackSize() < two->getStackSize()); }

Inventory::Inventory(void)
{
	this->init();

}

void Inventory::init() {
	std::cout<< "Created inv"<<std::endl;
	this->open = false;
	this->slots = 15;
	this->itemVector = std::vector<Item*>();
	selectedIndex = 0;
	sizeX = ScreenWidth / 2;
	sizeY = ScreenHeight / 20;
	posX = ScreenWidth / 2 - sizeX / 2;
	posY = ScreenHeight - sizeY - 10; //10 = margin from bottom


	slotWidth = ScreenWidth / 32;
	slotHeight = ScreenHeight / 18;
	itemWidth = ScreenWidth / 50;
	itemHeight = ScreenHeight / 30;

	int id = GameStateManager::Instance()->getImageLoader()->loadTileset("inv-background.png", 1095, 72);
	img = GameStateManager::Instance()->getImageLoader()->getMapImage(id);

	int singleId = GameStateManager::Instance()->getImageLoader()->loadTileset("single-inv-item.png", 69,69);
	singleImg = GameStateManager::Instance()->getImageLoader()->getMapImage(singleId);

	int singleSelectedId = GameStateManager::Instance()->getImageLoader()->loadTileset("single-inv-item-selected.png", 69,69);
	singleSelectedImg = GameStateManager::Instance()->getImageLoader()->getMapImage(singleSelectedId);

	std::cout << "Creating inv img" << std::endl;
}

void Inventory::cleanup() {

}

void Inventory::incrementSelectedIndex() {
	selectedIndex++;
	if (selectedIndex > this->slots - 1) {
		selectedIndex = 0;
	}
}

void Inventory::decrementSelectedIndex() {
	selectedIndex--;
	if (selectedIndex < 0) {
		selectedIndex = this->slots - 1;
	}
}

Item* Inventory::getSelectedItem() {
   	if (selectedIndex < this->getSize()) {
		return this->itemVector[selectedIndex];
	} else {
		return nullptr;
	}
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
				return false;
			}
		} else {
			//Try to up stacksize of an existing inventory slot
			while (item->getStackSize() > 0) {
				//	std::cout << "Item to add stacksize: " << item->getStackSize() << std::endl;
				if (inInvItem->getStackSize() >= inInvItem->getMaxStackSize()) {
					inInvItem = this->getItemById(item->getId(), false);
					if (inInvItem == nullptr && this->getSize() <= slots) {
						this->itemVector.push_back(item);
						break;
					}
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
			return false;
		}
	}

	if (item->getStackSize() <= 0) {
		delete item;
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

int Inventory::getItemCount(int itemID) 
{
	int amount = 0;
	for (size_t i = 0; i < this->itemVector.size(); i++) {
		if (this->itemVector[i] != NULL && this->itemVector[i]->getId() == itemID) {
			amount += this->itemVector[i]->getStackSize();
		}
	}
	return amount;
}

int Inventory::getStackCount(int itemID)
{
	int amount = 0;
	for (size_t i = 0; i < this->itemVector.size(); i++) {
		if (this->itemVector[i] != NULL && this->itemVector[i]->getId() == itemID) {
			amount++;
		}
	}
	return amount;
}

int Inventory::getSlotsFreedWhenDeleting(int itemID, int count)
{
	vector<Item*> stackVector;
	int slots = 0; 

	for (size_t i = 0; i < this->itemVector.size(); i++) {
		if (this->itemVector[i]->getId() == itemID) {
			stackVector.push_back(itemVector[i]);
		}
	}
	std::sort(stackVector.begin(), stackVector.end(), Inventory::stackSortFunction);
	for (size_t i = 0; i < stackVector.size(); i++) {
		if (stackVector[i]->getStackSize() <= count)
		{
			count -= stackVector[i]->getStackSize();
			slots++;
		}
		else
		{
			break;
		}
	}

	return slots;
}

void Inventory::deleteItem(int itemID, int count)
{
	vector<Item*> stackVector;

	for (size_t i = 0; i < this->itemVector.size(); i++) {
		if (this->itemVector[i]->getId() == itemID) {
			stackVector.push_back(itemVector[i]);
		}
	}
	std::sort(stackVector.begin(), stackVector.end(), Inventory::stackSortFunction);
	for (size_t i = 0; i < stackVector.size(); i++) {
		Item* stack = stackVector[i];
		if (stackVector[i]->getStackSize() <= count)
		{
			count -= stack->getStackSize();
			stack->setStackSize(stack->getStackSize() - stack->getStackSize());

			std::vector<Item*>::iterator it = std::find(this->itemVector.begin(), this->itemVector.end(), stack);
			delete *it;
			this->itemVector.erase(it);
		}
		else
		{
			stack->setStackSize(stack->getStackSize() - count);
			break;
		}
	}
}

void Inventory::deleteItemFromStack(Item* stack, int count) {
	stack->setStackSize(stack->getStackSize() - count);
	if (stack->getStackSize() <= 0) {
		std::vector<Item*>::iterator it = std::find(this->itemVector.begin(), this->itemVector.end(), stack);
		delete *it;
		this->itemVector.erase(it);
	}
}

void Inventory::interactCurrent(Player* p) {
	if (selectedIndex < this->getSize()) {
		Item* item = this->itemVector[selectedIndex];
		if (item != nullptr) {
			if (item->isConsumable()) {
				Consumable* c = (Consumable*)item;
				c->consume(p);
			} else if (item->isEquipable()) {
				Equipable* e = (Equipable*)item;
				e->equip(p);
			}
		}
	}
}

void Inventory::dropCurrent() {
	if (selectedIndex < this->getSize()) {
		Item* item = this->itemVector[selectedIndex];
		this->deleteItemFromStack(item, 1);
	}
}

bool Inventory::pickAxeSelected() {
	if (this->getSelectedItem() != nullptr) {
		if (this->getSelectedItem()->getId() == (int)Items::Pickaxe) {
			return true;
		}
	}
	return false;
}

bool Inventory::axeSelected() {
	if (this->getSelectedItem() != nullptr) {
		if (this->getSelectedItem()->getId() == (int)Items::Axe) {
			return true;
		}
	}
	return false;
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

int Inventory::getSlots() {
	return this->slots;
}

void Inventory::printInventory() {
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

bool Inventory::clicked(int x, int y, std::string mode, Player* player) {
	if (x >= startX && x <= endX && y >= startY  && y <= startY + slotHeight) {
		int clickedIndex = -1;

		for (int i = 0; i < this->slots; i++) {
			int startSlotX = startX + i*slotWidth;
			int endSlotX = startSlotX + slotWidth;

			if (x >= startSlotX && x <= endSlotX) {
				selectedIndex = i;
				break;
			}
		}
		if (mode == "use") {
			interactCurrent(player);
		}

		return true;
	}
	return false;

}

void Inventory::draw() {
	for (size_t i = 0; i < this->slots; i++) {


		int slotX =  posX + ScreenWidth / 32 +  i*(ScreenWidth / 32);
		int slotY = posY - 20;

		if (i == 0) {
			startX = slotX;
			startY = slotY;
		} else if (i == this->slots - 1){ 
			endX = slotX + slotWidth;
		}


		SDL_Rect slotRect;
		slotRect.x = slotX;
		slotRect.y = slotY;
		slotRect.w = slotWidth;
		slotRect.h = slotHeight;

		if (i == selectedIndex) {
			SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), singleSelectedImg->getTileSet(), NULL, &slotRect);
		} else {
			SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), singleImg->getTileSet(), NULL, &slotRect);
		}
		if (i < this->getSize()) {
			int itemX = slotX + slotWidth / 2 - itemWidth / 2;
			int itemY = slotY + slotHeight / 2 - itemHeight / 2;

			SDL_Rect imgRect;
			imgRect.x = itemX;
			imgRect.y = itemY;
			imgRect.w = itemWidth;
			imgRect.h = itemHeight;
			SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), this->itemVector[i]->getImage()->getTileSet(), NULL, &imgRect);
			if (this->itemVector[i]->getMaxStackSize() != 1) {
				GameStateManager::Instance()->sdlInitializer->drawText(
					std::string(std::to_string(this->itemVector[i]->getStackSize())), slotX + slotWidth - 4*(slotWidth / 10), slotY + slotHeight - 5*(slotHeight / 10),10, 22
					);
			}
		}
	}
}

int Inventory::getStartingX() {
	return this->startX;
}

int Inventory::getStartingY() {
	return this->startY;
}

int Inventory::getWidth() {
	return this->slots * this->slotWidth;
}


Inventory::~Inventory(void)
{
}
