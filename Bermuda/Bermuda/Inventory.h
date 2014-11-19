#pragma once
#include <vector>

class Item;
class Image;
class Player;
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

	void draw();

	Item* getItemById(int id, bool full);

	int getSize();
	void setSize(int size);

	void toggleInventory();
	bool isOpen();

	void printInventory();

	~Inventory(void);
private:
	//Draw
	Image* img;
	int posX;
	int posY;
	int sizeX;
	int sizeY;

	//Selected Index
	int selectedIndex;
	bool open;
	int slots; //Total item slots
	std::vector<Item*> itemVector;
};

