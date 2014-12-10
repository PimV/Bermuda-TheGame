#include "Branch.h"
#include "PlayState.h"
#include "ItemFactory.h"
#include "Items.h"
#include "Overlays.h"

Branch::Branch(int id, double x, double y, Image* branchImage) : 
	Entity(id,x,y), 
	DrawableEntity(id,x,y, branchImage), 
	InteractableEntity(id,x,y, -25, -25, this->getWidth() + 50, this->getHeight() + 50)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::branch));
	this->setHighlightTexture(this->getCanInteractTexture());
}

void Branch::update(double dt) {

}

void Branch::interact(Player* player)
{
	player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Branch));
	this->setDestroyedState();
}

void Branch::setDestroyedState()
{
	this->setHighlighted(false);
	PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
}

Branch::~Branch()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}
