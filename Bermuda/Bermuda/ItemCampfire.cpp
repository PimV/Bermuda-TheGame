#include "ItemCampfire.h"
#include "Campfire.h"
#include "GameStateManager.h"


ItemCampfire::ItemCampfire(Image* image)
{
	this->setImage(image);
	init();
}

void ItemCampfire::init()
{
	this->setId((int)Items::Campfire);

	this->itemTypes = std::vector<ItemType>();
	this->itemTypes.push_back(ItemType::Buildable);
	this->setMaxStackSize(1);
	this->setStackSize(1);
}

void ItemCampfire::use(Player* p)
{
	int x = p->getX() + p->getWidth() + 10;
	int y = p->getY() + p->getHeight() - 52;

	Campfire* campfire = new Campfire(0, x, y, 300, GameStateManager::Instance()->getImageLoader()->loadTileset("Objects\\Campfire 50x52.png", 50, 52));

	//TODO: Somehow check collision? 
	//if collision, delete Campfire

	p->getInventory()->deleteItemFromStack(this, 1);
}

ItemCampfire::~ItemCampfire()
{
}
