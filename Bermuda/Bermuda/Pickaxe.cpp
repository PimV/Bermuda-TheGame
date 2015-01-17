#include "Pickaxe.h"
#include "PlayState.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"

Pickaxe::Pickaxe(int id, double x, double y, Image* pickaxeImage) : 
	Entity(id,x,y), 
	DrawableEntity(id,x,y, pickaxeImage), 
	InteractableEntity(id,x,y, -25, -25, this->getWidth() + 50, this->getHeight() + 50)
{
	PlayState::Instance()->getMainEntityContainer()->getBackgroundContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void Pickaxe::update(double dt) {

}

void Pickaxe::interact(Player* player)
{
	player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Pickaxe));
	PlayState::Instance()->getMainEntityContainer()->getBackgroundContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}


Pickaxe::~Pickaxe()
{
	PlayState::Instance()->getMainEntityContainer()->getBackgroundContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}
