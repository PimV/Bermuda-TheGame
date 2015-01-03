#include "Crafting.h"
#include "ItemFactory.h"
#include <iostream>
#include "header_loader.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "ItemFactory.h"



Crafting::Crafting(Inventory* inv)
{
	this->init(inv);
}

void Crafting::init(Inventory* inv)
{
	//TODO: add to GUI container
	this->open = false;
	this->inventory = inv;
	this->createRecipes();

	selectedCraftItemIndex = 0;
	itemsPerRow = 15;

	slotWidth = ScreenWidth / 32;
	slotHeight = ScreenHeight / 18;
	itemWidth = ScreenWidth / 50;
	itemHeight = ScreenHeight / 30;


	this->buildMenu();
}

void Crafting::buildMenu() {
	//Set images
	int bgImageId = PlayState::Instance()->getImageLoader()->loadTileset("textures\\menuBackground.png", 960, 720);
	bgImg = PlayState::Instance()->getImageLoader()->getMapImage(bgImageId);

	int slotId = PlayState::Instance()->getImageLoader()->loadTileset("single-inv-item.png", 69, 69);
	slotImg = PlayState::Instance()->getImageLoader()->getMapImage(slotId);

	int selectedSlotId = PlayState::Instance()->getImageLoader()->loadTileset("single-inv-item-selected.png", 69, 69);
	selectedSlotImg = PlayState::Instance()->getImageLoader()->getMapImage(selectedSlotId);

	int cancelId = PlayState::Instance()->getImageLoader()->loadTileset("textures\\cancelButton.png", 100, 30);
	cancelImg = PlayState::Instance()->getImageLoader()->getMapImage(cancelId);

	int acceptId = PlayState::Instance()->getImageLoader()->loadTileset("textures\\craftButton.png", 100, 30);
	acceptImg = PlayState::Instance()->getImageLoader()->getMapImage(acceptId);

	int acceptGreyedId = PlayState::Instance()->getImageLoader()->loadTileset("textures\\craftButtonGreyed.png", 100, 30);
	acceptGreyedImg = PlayState::Instance()->getImageLoader()->getMapImage(acceptGreyedId);

	int infoId = PlayState::Instance()->getImageLoader()->loadTileset("textures\\infoImg.png", 1000, 150);
	infoImg = PlayState::Instance()->getImageLoader()->getMapImage(infoId);

	//Set rectangles
	bgRect.x = ScreenWidth / 6;
	bgRect.y = ScreenHeight / 6;
	bgRect.w = 2*(ScreenWidth / 3);
	bgRect.h = 2*(ScreenHeight / 3);

	infoRect.x = ScreenWidth / 6 + 50;
	infoRect.y = ScreenHeight / 6 + ScreenHeight / 3;
	infoRect.w =  2 * (ScreenWidth / 3) - 100;
	infoRect.h = 150;

	acceptRect.x = ScreenWidth / 6 + 2*(ScreenWidth / 3) - 100 - 50;
	acceptRect.y = ScreenHeight / 6 + 2*(ScreenHeight / 3) - 60;
	acceptRect.w = 100;
	acceptRect.h = 30;

	cancelRect.x = ScreenWidth / 6 + 50;
	cancelRect.y = ScreenHeight / 6 + 2*(ScreenHeight / 3) - 60;
	cancelRect.w = 100;
	cancelRect.h = 30;
}

void Crafting::createRecipes()
{
	this->recipes[Items::Axe][Items::Wood] = 2;
	this->recipes[Items::Axe][Items::Rock] = 2;
	this->recipes[Items::GoldenAxe][Items::Wood] = 2;
	this->recipes[Items::GoldenAxe][Items::Gold] = 4;
	this->recipes[Items::Pickaxe][Items::Wood] = 2;
	this->recipes[Items::Pickaxe][Items::Rock] = 2;
	this->recipes[Items::GoldenPickaxe][Items::Wood] = 2;
	this->recipes[Items::GoldenPickaxe][Items::Gold] = 4;
	this->recipes[Items::Campfire][Items::Wood] = 3;
	this->recipes[Items::Campfire][Items::Rock] = 3;
	this->recipes[Items::Spear][Items::Wood] = 6;
	this->recipes[Items::Spear][Items::Rock] = 4;
	this->recipes[Items::Spear][Items::Flint] = 1;

}

bool Crafting::canCraft(Items item)
{
	map<Items, map<Items, int>>::iterator it = recipes.find(item);
	map<Items, int> resources;
	if (it != recipes.end())
	{
		//recipe found;
		resources = recipes[item];
		int slotsFreedByCrafting = 0;
		for (pair<Items, int> pair : resources)
		{
			int itemID = (int)pair.first;
			int amount = pair.second;

			//Check if enough resources are in the inventory.
			if (this->inventory->getItemCount(itemID) >= amount)
			{
				slotsFreedByCrafting += this->inventory->getSlotsFreedWhenDeleting(itemID, amount);
			}
			else
			{
				return false;
			}
		}

		//Enough resources are available. Check if a slot is available after crafting.
		if (this->inventory->getSize() - slotsFreedByCrafting < this->inventory->getSlots())
		{
			return true;
		}
	}

	return false;
}

void Crafting::craftItem(Items item)
{
	if (canCraft(item))
	{
		//Remove resources from inventory
		for (pair<Items, int> pair : recipes[item])
		{
			int itemID = (int)pair.first;
			int amount = pair.second;
			this->inventory->deleteItem(itemID, amount);
		}

		//Create item
		this->inventory->addItem(ItemFactory::Instance()->createItem(item));

	}
}

void Crafting::toggleCraftMenu()
{
	open = !open;
}

void Crafting::clicked(int x, int y, std::string mode, Player* player) {
	std::cout << "Start[" << this->startX << ":" << this->startY << "]" << std::endl;
	std::cout << "End[" << this->endX << ":" << this->endY << "]" << std::endl;

	if (this->open) {
		//Check if clicked on slots
		if (x >= this->startX && x <= this->endX && y >= this->startY  && y <= this->endY) {
			int clickedIndex = this->selectedCraftItemIndex;

			int rowClicked = -1;
			int columnClicked = 0;

			for (int i = 0; i < this->recipes.size(); i++) {
				if (i % itemsPerRow == 0) {
					rowClicked++;
				}
				columnClicked = i % itemsPerRow;
				int startSlotX = startX + columnClicked*50;
				int endSlotX = startSlotX + 50;
				int startSlotY = startY + rowClicked*50;
				int endSlotY = startSlotY + 50;

				if (x >= startSlotX && x <= endSlotX && y >= startSlotY && y <= endSlotY) {
					clickedIndex = i;
					this->selectedCraftItemIndex = clickedIndex;
					break;
				}
			}
		}

		//Check if clicked on accept
		if (x >= acceptRect.x && x <= acceptRect.x + acceptRect.w
			&& y >= acceptRect.y && y <= acceptRect.y + acceptRect.h) {
				if (canCraft(this->selectedCraftItem)) {
					craftItem(this->selectedCraftItem);
				} 
		}
		//Check if clicked on cancel
		if (x >= cancelRect.x && x <= cancelRect.x + cancelRect.w
			&& y >= cancelRect.y && y <= cancelRect.y + cancelRect.h) {
				this->open = false;
		}
	}


}

bool Crafting::isOpen() {
	return open;
}

void Crafting::draw()
{
	if (this->open) {
		//Background
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), bgImg->getTileSet(), bgImg->getCroppingRect(), &bgRect);

		//Items
		int startOffsetX = ScreenWidth / 6 + 50;
		int startOffsetY = ScreenHeight / 6 + 50;
		int rows = -1;
		int columns = 0;

		int elements = 0;



		for (auto it = recipes.begin(); it != recipes.end(); ++it) {
			if (elements == 0) {
				startX = startOffsetX;
				startY = startOffsetY;
			}


			//Go to next row
			if (elements % itemsPerRow == 0) {
				rows++;
			}
			//Reset column width if row increased
			columns = elements % itemsPerRow;

			//Create slotRectangle
			SDL_Rect slotRect;
			slotRect.x = startOffsetX + columns*50;
			slotRect.y = startOffsetY + rows*50;
			slotRect.w = 45;
			slotRect.h = 45;
			if (elements == this->selectedCraftItemIndex) {
				SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), selectedSlotImg->getTileSet(), selectedSlotImg->getCroppingRect(), &slotRect);
				if (this->selectedCraftItem != it->first) {
					this->selectedCraftItem = it->first;
				}
			} else {
				SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), slotImg->getTileSet(), slotImg->getCroppingRect(), &slotRect);
			}

			SDL_Rect itemRect;
			itemRect.x = startOffsetX + columns*50 + 8;
			itemRect.y = startOffsetY + rows*50 + 8;
			itemRect.w = 30;
			itemRect.h = 30;

			Image* itemImg = ItemFactory::Instance()->getItemImage(it->first);
			SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), itemImg->getTileSet(), itemImg->getCroppingRect(), &itemRect);

			elements++;
		}

		endX = startOffsetX + columns * 50 + 45;
		endY = startOffsetY + rows * 50 + 45;

		//Draw info rectangle
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), infoImg->getTileSet(), infoImg->getCroppingRect(), &infoRect);

		std::string itemToCraft = "To craft a(n) ";
		itemToCraft.append(item_strings[(int)this->selectedCraftItem]);
		itemToCraft.append(", you require the following item(s):");

		GameStateManager::Instance()->sdlInitializer->drawText(itemToCraft, infoRect.x + 15, infoRect.y, 100, 34, 28);


		int recipeElements = 0;
		for (auto it = recipes[this->selectedCraftItem].begin(); it != recipes[this->selectedCraftItem].end(); ++it) {
			std::string recipeLine = item_strings[(int)it->first];
			recipeLine.append(" x" + std::to_string(it->second));

			GameStateManager::Instance()->sdlInitializer->drawText(recipeLine, infoRect.x + 15, infoRect.y + 50 + recipeElements*20, 100, 26, 26);
			recipeElements++;
		}

		//Draw accept button
		if (canCraft(this->selectedCraftItem)) {
			SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), acceptImg->getTileSet(), acceptImg->getCroppingRect(), &acceptRect);
		} else {
			SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), acceptGreyedImg->getTileSet(), acceptGreyedImg->getCroppingRect(), &acceptRect);
		}

		//Draw cancel button
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), cancelImg->getTileSet(), cancelImg->getCroppingRect(), &cancelRect);


	}
}

void Crafting::cleanup()
{
	//Nothing to clean for now.
}

Crafting::~Crafting()
{
	this->cleanup();
}
