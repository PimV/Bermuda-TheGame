#pragma once
#include "ImageLoader.h"
#include "Image.h"
#include "header_loader.h"
#include "ItemCarrot.h"
#include "ItemApple.h"
#include "ItemWater.h"
#include "ItemFish.h"
#include "ItemRock.h"
#include "ItemWood.h"
#include "ItemGold.h"
#include "ToolAxe.h"
#include "ToolPickaxe.h"
#include "ToolFlint.h"
#include "WeaponSpear.h"
#include "Items.h"
#include "Item.h"
#include <map>

class ItemFactory
{
private:
	static ItemFactory itemFactory;
	std::map<Items, Image*> itemImages;

public:
	ItemFactory();
	void loadItemTileSets(ImageLoader* imgLoader);
	Item* createItem(Items item);
	Image* getItemImage(Items item);

	virtual ~ItemFactory();
	static ItemFactory* Instance() {
		return &itemFactory;
	};
};

