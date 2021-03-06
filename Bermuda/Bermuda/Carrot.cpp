#include "Carrot.h"
#include "PlayState.h"
#include "ItemFactory.h"
#include "Items.h"
#include "Overlays.h"

Carrot::Carrot(int id, double x, double y, Image* carrotImage) : 
	Entity(id,x,y), 
	DrawableEntity(id,x,y, carrotImage), 
	InteractableEntity(id,x,y, -25, -25, this->getWidth() + 50, this->getHeight() + 50)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::carrot));
	this->setHighlightTexture(this->getCanInteractTexture());
}

void Carrot::update(double dt) {

}

void Carrot::interact(Player* player)
{
	player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Carrot));
	player->getStatusTracker()->addAchievementCount(AchievementsEnum::CARROTPICKED);
	this->setDestroyedState();
}

void Carrot::setDestroyedState()
{
	this->setHighlighted(false);
	PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
}

Carrot::~Carrot()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}
