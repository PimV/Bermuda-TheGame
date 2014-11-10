#pragma once
#include "ImageLoader.h"
#include "Image.h"
#include "header_loader.h"
#include "ItemCarrot.h"
#include "ItemFish.h"
#include "ItemRock.h"
#include "ItemWood.h"
#include "ToolAxe.h"
#include "ToolPickaxe.h"
#include <map>

class ItemFactory
{
private:
	static ItemFactory itemFactory;
	std::map<std::string, Image*> itemImages;

public:
	ItemFactory();
	void loadItemTileSets(ImageLoader* imgLoader);
	ItemCarrot* createCarrot();
	ItemFish* createFish();
	ItemRock* createRock();
	ItemWood* createWood();
	ToolAxe* createAxe();
	ToolPickaxe* createPickaxe();

	~ItemFactory();
	static ItemFactory* Instance() {
		return &itemFactory;
	};
};

