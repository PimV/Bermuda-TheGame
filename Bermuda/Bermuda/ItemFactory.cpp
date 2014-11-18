#include "ItemFactory.h"

ItemFactory ItemFactory::itemFactory;

ItemFactory::ItemFactory(void)
{
}

void ItemFactory::loadItemTileSets(ImageLoader* imgLoader)
{
	itemImages["carrot"] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemCarrot.png", 30, 22));
	itemImages["fish"] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemFish.png", 30, 24));
	itemImages["apple"] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemApple.png", 30,34));;
	itemImages["rock"] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemRock.png", 30,22));
	itemImages["wood"] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemLogs.png", 32,25));
	itemImages["gold"] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemGold.png", 34,22));
	itemImages["water"] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemWater.png", 22,34));
	itemImages["axe"] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\Iron_pickaxe.png", 32,32));
	itemImages["pickaxe"] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\Iron_axe.png", 22,27));
	itemImages["flint"] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ToolFlint.png", 38,22));;
}

ItemCarrot* ItemFactory::createCarrot()
{
	return new ItemCarrot(itemImages["carrot"]);
}

ItemApple* ItemFactory::createApple()
{
	return new ItemApple(itemImages["apple"]);
}

ItemWater* ItemFactory::createWater()
{
	return new ItemWater(itemImages["water"]);
}

ItemFish* ItemFactory::createFish()
{
	return new ItemFish(itemImages["fish"]);
}

ItemRock* ItemFactory::createRock()
{
	return new ItemRock(itemImages["rock"]);
}

ItemGold* ItemFactory::createGold()
{
	return new ItemGold(itemImages["gold"]);
}

ItemWood* ItemFactory::createWood()
{
	return new ItemWood(itemImages["wood"]);
}

ToolAxe* ItemFactory::createAxe()
{
	return new ToolAxe(itemImages["axe"]);
}

ToolPickaxe* ItemFactory::createPickaxe()
{
	return new ToolPickaxe(itemImages["pickaxe"]);
}

ToolFlint* ItemFactory::createFlint()
{
	return new ToolFlint(itemImages["flint"]);
}

ItemFactory::~ItemFactory(void)
{
}
