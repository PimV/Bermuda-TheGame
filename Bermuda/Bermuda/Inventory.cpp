#include "Inventory.h"
#include <iostream>
#include "Items.h"
#include "Item.h"
#include "Image.h"
#include "Consumable.h"
#include "Equipable.h"
#include "Player.h"




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


	int id = GameStateManager::Instance()->getImageLoader()->loadTileset("inv-background.png", 1095, 72);
	img = GameStateManager::Instance()->getImageLoader()->getMapImage(id);
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
			}
		} else {
			//Try to up stacksize of an existing inventory slot
			while (item->getStackSize() > 0) {
				//	std::cout << "Item to add stacksize: " << item->getStackSize() << std::endl;
				if (inInvItem->getStackSize() >= inInvItem->getMaxStackSize()) {
					inInvItem = this->getItemById(item->getId(), false);
					if (inInvItem == nullptr) {
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
//Mem leak fixed?
void Inventory::deleteItem(Item* item, int count) {

	item->setStackSize(item->getStackSize() - count);

	if (item->getStackSize() <= 0) {
		std::vector<Item*>::iterator it = std::find(this->itemVector.begin(), this->itemVector.end(), item);
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
		this->deleteItem(item, 1);
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
	//int y = 50;
	//for (size_t i = 0; i < 20; i++) {
	//	if (i < this->getSize()) {
	//		GameStateManager::Instance()->sdlInitializer->drawText(
	//			std::string(item_strings[this->itemVector[i]->getId()] + std::string(":") + std::to_string(this->itemVector[i]->getStackSize())), 20, 24*i + 5,100, 32
	//			);
	//	}
	//}

	//SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), drawImage->getTileSet(), drawImage->getCroppingRect(), sizeRect);

	SDL_Rect txtRect;
	txtRect.x = posX;
	txtRect.y = posY;
	txtRect.w = sizeX;
	txtRect.h = sizeY;


	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), img->getTileSet(), NULL, &txtRect);


	int offset = 0;
	for (size_t i = 0; i < this->slots; i++) {
		if (i < this->getSize()) {
			SDL_Rect imgRect;
			imgRect.x = posX + (i *(sizeX / 15)) + 10;
			imgRect.y = posY + sizeY / 2 - (ScreenHeight / 30) / 2;
			imgRect.w = ScreenWidth / 50;
			imgRect.h = ScreenHeight / 30;
			SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), this->itemVector[i]->getImage()->getTileSet(), NULL, &imgRect);
			if (this->itemVector[i]->getMaxStackSize() != 1) {
				GameStateManager::Instance()->sdlInitializer->drawText(
					std::string(std::to_string(this->itemVector[i]->getStackSize())), posX + (i *(sizeX / 15)) + (sizeX / 15) - 15, posY  + sizeY - 22,10, 22
					);
			}
		}
		if (i == selectedIndex) {
			
			int x = posX + (i *(sizeX / 15));

			SDL_Rect rectToDraw = {
				x,
				posY,
				(sizeX / 15),
				sizeY
			}; 
			SDL_SetRenderDrawColor(GameStateManager::Instance()->sdlInitializer->getRenderer(), 0, 255, 0, 255);
			SDL_RenderDrawRect(GameStateManager::Instance()->sdlInitializer->getRenderer(), &rectToDraw);
			SDL_SetRenderDrawColor(GameStateManager::Instance()->sdlInitializer->getRenderer(), 0, 0, 0, 255);
		}
	}
}


Inventory::~Inventory(void)
{
}
