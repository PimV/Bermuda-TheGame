#include "ItemFactory.h"

ItemFactory ItemFactory::itemFactory;

ItemFactory::ItemFactory(void)
{
}

void ItemFactory::loadItemTileSets(ImageLoader* imgLoader)
{
	itemImages[Items::Carrot] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemCarrot.png", 30, 22));
	itemImages[Items::Fish] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemFish.png", 30, 24));
	itemImages[Items::Apple] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemApple.png", 30,34));;
	itemImages[Items::Rock] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemRock.png", 30,22));
	itemImages[Items::Wood] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemLogs.png", 32,25));
	itemImages[Items::Gold] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemGold.png", 34,22));
	itemImages[Items::Water] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ItemWater.png", 22,34));
	itemImages[Items::Pickaxe] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ToolPickaxe.png", 32,32));
	itemImages[Items::Axe] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ToolAxe.png", 22,27));
	itemImages[Items::Flint] = imgLoader->getMapImage(imgLoader->loadTileset("Items\\ToolFlint.png", 38,22));;
}

Item* ItemFactory::createItem(Items item)
{
	switch (item)
	{
	case Items::Carrot:
		return new ItemCarrot(itemImages[Items::Carrot]);
		break;
	case Items::Apple:
		return new ItemApple(itemImages[Items::Apple]);
		break;
	case Items::Water:
		return new ItemWater(itemImages[Items::Water]);
		break;
	case Items::Fish:
		return new ItemFish(itemImages[Items::Fish]);
		break;
	case Items::Rock:
		return new ItemRock(itemImages[Items::Rock]);
		break;
	case Items::Gold:
		return new ItemGold(itemImages[Items::Gold]);
		break;
	case Items::Wood:
		return new ItemWood(itemImages[Items::Wood]);
		break;
	case Items::Axe:
		return new ToolAxe(itemImages[Items::Axe]);
		break;
	case Items::Pickaxe:
		return new ToolPickaxe(itemImages[Items::Pickaxe]);
		break;
	case Items::Flint:
		return new ToolFlint(itemImages[Items::Flint]);
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

ItemFactory::~ItemFactory(void)
{
}
