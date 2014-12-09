#include "ItemFactory.h"
#include "ItemCarrot.h"
#include "ItemApple.h"
#include "ItemWater.h"
#include "ItemFish.h"
#include "ItemRock.h"
#include "ItemWood.h"
#include "ItemGold.h"
#include "ItemCampfire.h"
#include "ItemMeat.h"
#include "ToolAxe.h"
#include "ToolPickaxe.h"
#include "ToolFlint.h"

ItemFactory ItemFactory::itemFactory;

ItemFactory::ItemFactory()
{
}

void ItemFactory::loadItemTileSets(ImageLoader* imgLoader)
{
	itemImages[Items::Carrot] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemCarrot.png", 30, 22));
	itemImages[Items::Fish] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemFish.png", 30, 24));
	itemImages[Items::Apple] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemApple.png", 30,34));
	itemImages[Items::Rock] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemRock.png", 30,22));
	itemImages[Items::Wood] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemLogs.png", 32,25));
	itemImages[Items::Gold] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemGold.png", 34,22));
	itemImages[Items::Water] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemWater.png", 22,34));
	itemImages[Items::Campfire] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemCampfire.png", 38, 22));
	itemImages[Items::Pickaxe] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ToolPickaxe.png", 32,32));
	itemImages[Items::Axe] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ToolAxe.png", 22,27));
	itemImages[Items::Flint] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ToolFlint.png", 38,22));
	itemImages[Items::Spear] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\WeaponSpear.png", 40,39));
	itemImages[Items::Meat] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemMeat.png", 29,31));
}

Item* ItemFactory::createItem(Items item)
{
	switch (item)
	{
	case Items::Carrot:
		return new ItemCarrot(itemImages[item]);
		break;
	case Items::Apple:
		return new ItemApple(itemImages[item]);
		break;
	case Items::Water:
		return new ItemWater(itemImages[item]);
		break;
	case Items::Fish:
		return new ItemFish(itemImages[item]);
		break;
	case Items::Rock:
		return new ItemRock(itemImages[item]);
		break;
	case Items::Gold:
		return new ItemGold(itemImages[item]);
		break;
	case Items::Wood:
		return new ItemWood(itemImages[item]);
		break;
	case Items::Campfire:
		return new ItemCampfire(itemImages[item]);
		break;
	case Items::Axe:
		return new ToolAxe(itemImages[item]);
		break;
	case Items::Pickaxe:
		return new ToolPickaxe(itemImages[item]);
		break;
	case Items::Flint:
		return new ToolFlint(itemImages[item]);
		break;
	case Items::Spear:
		return new WeaponSpear(itemImages[item]);
		break;
	case Items::Meat:
		return new ItemMeat(itemImages[item]);
		break;
	default:
		return nullptr;
		break;
	}
}

Image* ItemFactory::getItemImage(Items item)
{
	return itemImages[item];
}

ItemFactory::~ItemFactory()
{
}
