#pragma once
#include "ImageLoader.h"
#include "Image.h"
#include "header_loader.h"
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

	~ItemFactory();
	static ItemFactory* Instance() {
		return &itemFactory;
	};
};

