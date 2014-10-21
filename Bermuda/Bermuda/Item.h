#pragma once
//Includes
#include "ItemType.h"
#include <vector>

//Forward Declarations
class Image;

//Class definition
class Item
{
public:
	Item(int id, int maxStackSize, bool stackable, Image* image);

	void init();
	void cleanup();

	int getId();
	int getStackSize();
	int getMaxStackSize();
	void setStackSize(int size);

	void addItemType(ItemType* itemType);
	bool hasItemType(ItemType* itemType);
	void removeItemType(ItemType* itemType);
	std::vector<ItemType*> getItemTypes();

	bool getStackable();


	~Item();
private:
	int id;
	int stackSize;
	int maxStackSize;
	bool stackable;
	Image* image;
	std::vector<ItemType*> itemTypes;
};

