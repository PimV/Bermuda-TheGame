#pragma once
//Includes
#include "ItemType.h"
#include "Image.h"
#include "Player.h"
#include <vector>

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

	Item* getSelectedItem();

	int getMaxStackSize();	
	void setMaxStackSize(int size);

	bool getStackable();
	void setStackable(bool stackable);

	Image* getImage();
	void setImage(Image* image);

	virtual void use(Player* p);

	void addItemType(ItemType itemType);
	bool hasItemType(ItemType itemType);
	void removeItemType(ItemType itemType);
	std::vector<ItemType> getItemTypes();

	bool isConsumable();
	bool isEquipable();

	virtual ~Item();
private:
	int id;
	int stackSize;
	int maxStackSize;
	bool stackable;
	Image* image;

protected:
	std::vector<ItemType> itemTypes;
};

