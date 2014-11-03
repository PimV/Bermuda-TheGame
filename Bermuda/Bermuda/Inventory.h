#pragma once
#include <vector>

class Item;
class Inventory
{
public:
	Inventory(void);

	void init();
	void cleanup();

	bool addItem(Item* item);
	bool hasItem(Item* item);
	void deleteItem(Item* item, int count);
	std::vector<Item*> getItems();

	void draw();

	Item* getItemById(int id, bool full);

	int getSize();
	void setSize(int size);

	void toggleInventory();
	bool isOpen();

	void printInventory();

	~Inventory(void);
private:
	bool open;
	int slots; //Total item slots
	std::vector<Item*> itemVector;
};

