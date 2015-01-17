#include "Fish.h"
#include "PlayState.h"
#include "ItemFactory.h"
#include "Items.h"
#include "Overlays.h"

Fish::Fish(int id, double x, double y, Image* fishImage) :
	Entity(id,x,y), 
	DrawableEntity(id,x,y, fishImage), 
	InteractableEntity(id,x,y, -64, -64, 192, 192)
{
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);

	this->destroyed = false;
	this->respawnTime = GameTimer::Instance()->getFullDayLength() * 10;
	this->interactTime = 9000;

	this->animationType = AnimationEnumType::AttackSpear;

	this->setCanInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::fish));
	this->setCantInteractTexture(PlayState::Instance()->getImageLoader()->getOverLayImage(Overlays::fishCant));
	
	this->setHighlightTexture(this->getCantInteractTexture());
}

bool Fish::canInteract(Player* player) {
	if (player->getInventory()->spearSelected()) {
		this->setHighlightTexture(this->getCanInteractTexture());
	} else {
		this->setHighlightTexture(this->getCantInteractTexture());
	}
	return player->getInventory()->spearSelected();
}

void Fish::interact(Player* player) 
{
	if (player->getInventory()->spearSelected()) {
		InteractableEntity::interact(player);
		player->setCorrectToolSelected(true);
		if (this->trackInteractTimes()) {
			player->setCorrectToolSelected(false);
			this->setDestroyedState();
			player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Fish));
			player->getStatusTracker()->addAchievementCount(AchievementsEnum::FISHESFISHED);
		}
	} else {
		player->setCorrectToolSelected(false);
	}
}

void Fish::update(double dt) 
{
	if (this->destroyed) {
		if (this->timeDestroyed + respawnTime < GameTimer::Instance()->getGameTime()) {
			this->respawn();
		}
	}
}

void Fish::respawn() 
{
	this->destroyed = false;
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
}

void Fish::setDestroyedState() 
{
	this->setHighlighted(false);
	this->timeDestroyed = GameTimer::Instance()->getGameTime();
	this->destroyed = true;
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	currentInteractTime = 0;
}

Fish::~Fish()
{
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
}
