#pragma once
#include "Inventory.h"
#include "Items.h"
#include <map>
class ItemFactory;
class Crafting
{
private:
	bool open;
	Inventory* inventory;
	std::map<Items, std::map<Items, int>> recipes;
	Image* bgImg;
	Image* acceptImg;
	Image* cancelImg;
	Image* slotImg;
	Image* selectedSlotImg;
	Image* acceptGreyedImg;
	Image* infoImg;


	void createRecipes();
	void buildMenu();

	int startX;
	int endX;
	int startY;
	int endY;

	int slotWidth;
	int slotHeight;
	int itemWidth;
	int itemHeight;

	int itemsPerRow;

	int selectedCraftItemIndex;
	Items selectedCraftItem;

	SDL_Rect bgRect;
	SDL_Rect infoRect;
	SDL_Rect acceptRect;
	SDL_Rect cancelRect;

public:
	Crafting(Inventory* inv);
	void init(Inventory* inv);
	bool canCraft(Items item);
	void craftItem(Items item);
	void draw();
	void clicked(int x, int y, std::string mode, Player* player);
	void toggleCraftMenu();
	bool isOpen();
	void cleanup();
	virtual ~Crafting();
};