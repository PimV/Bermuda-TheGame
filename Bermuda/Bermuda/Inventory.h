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

	Item* getItemById(int id, bool full);

	int getSize();
	void setSize(int size);

	void printInventory();

	~Inventory(void);
private:
	int slots; //Total item slots
	std::vector<Item*> itemVector;
};

