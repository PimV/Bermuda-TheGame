#pragma once
#include <vector>

class Item;
class Image;
class Player;
class Equipable;
class Inventory
{
public:
	Inventory(void);

	void init();
	void cleanup();

	void incrementSelectedIndex();
	void decrementSelectedIndex();

	void interactCurrent(Player* p);
	void dropCurrent();
	Item* getSelectedItem();

	bool addItem(Item* item);
	bool hasItem(Item* item);
	bool hasItemById(int itemId);
	void deleteItem(Item* item, int count);
	std::vector<Item*> getItems();

	bool hasAxe();
	bool hasPickaxe();

	bool axeSelected();
	bool pickAxeSelected();

	void draw();

	Item* getItemById(int id, bool full);

	int getSize();
	void setSize(int size);
	int getSlots();

	void toggleInventory();
	bool isOpen();

	bool clicked(int x, int y, std::string mode, Player* player);

	void printInventory();

	~Inventory(void);
private:
	//Draw
	Image* img;
	Image* singleImg;
	Image* singleSelectedImg;
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
};

