#pragma once
#include "Image.h"
#include <vector>

class Player;
class Item;

class Inventory
{
public:
	Inventory();

	void init();
	void cleanup();

	void incrementSelectedIndex();
	void decrementSelectedIndex();

	void interactCurrent(Player* p);
	void interacSpecific(Player* p, int stackIndex);
	void dropCurrent();
	Item* getSelectedItem();

	bool addItem(Item* item);
	bool hasItem(Item* item);
	bool hasItemById(int itemId);
	int getItemCount(int itemID);
	int getStackCount(int itemID);
	int getSlotsFreedWhenDeleting(int itemID, int count);
	void deleteItem(int itemID, int count);
	void deleteItemFromStack(Item* stack, int count);
	std::vector<Item*> getItems();

	bool hasAxe();
	bool hasPickaxe();

	bool axeSelected();
	bool pickAxeSelected();

	void draw();
	int getStartingX();
	int getStartingY();
	int getWidth();

	Item* getItemById(int id, bool full);

	int getSize();
	void setSize(int size);
	int getSlots();

	void toggleInventory();
	bool isOpen();

	void selectStack(Item* stack);
	void setSelectedIndex(int index);
	bool clicked(int x, int y, std::string mode, Player* player);

	void printInventory();

	virtual ~Inventory();
private:
	//Draw
	Image* img;
	Image* singleImg;
	Image* singleSelectedImg;
	Image* singleSelectedYellow;
	Image* singleSelectedRed;
	int posX;
	int posY;
	int sizeX;
	int sizeY;
	
	int startX;
	int endX;
	int startY;

	int slotWidth;
	int slotHeight; 
	int itemWidth;
	int itemHeight;

	//Selected Index
	int selectedIndex;
	bool open;
	int slots; //Total item slots
	std::vector<Item*> itemVector;

	static bool stackSortFunction(Item* one, Item* two);
};

