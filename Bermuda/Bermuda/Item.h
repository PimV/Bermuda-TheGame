#pragma once
//Includes
#include "ItemType.h"
#include "Items.h"
#include "GameStateManager.h"
#include <vector>

//Forward Declarations
class Image;

//Class definition
class Item
{
public:
	Item();

	void init();
	void cleanup();

	int getId();
	void setId(int id);
	int getStackSize();
	void setStackSize(int size);
	int getMaxStackSize();	
	void setMaxStackSize(int size);
	bool getStackable();
	void setStackable(bool stackable);
	Image* getImage();
	void setImage(Image* image);

	void addItemType(ItemType itemType);
	bool hasItemType(ItemType itemType);
	void removeItemType(ItemType itemType);
	std::vector<ItemType> getItemTypes();




	~Item();
private:
	int id;
	int stackSize;
	int maxStackSize;
	bool stackable;
	Image* image;
	ImageLoader* imgLoader;

protected:
	std::vector<ItemType> itemTypes;
};

