#include "Axe.h"
#include "PlayState.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"

Axe::Axe(int id, double x, double y, Image* axeImage) : 
	Entity(id,x,y), 
	DrawableEntity(id,x,y, axeImage), 
	InteractableEntity(id,x,y, -25, -25, this->getWidth() + 50, this->getHeight() + 50)
{
	PlayState::Instance()->getMainEntityContainer()->getBackgroundContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void Axe::update(double dt) {

}

void Axe::interact(Player* player)
{
	player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Axe));
	PlayState::Instance()->getMainEntityContainer()->getBackgroundContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}


Axe::~Axe()
{
}
