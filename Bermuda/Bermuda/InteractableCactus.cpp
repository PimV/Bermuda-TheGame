#include "InteractableCactus.h"
#include "PlayState.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"

InteractableCactus::InteractableCactus(int id, double x, double y, Image* cactusImage, Image* stumpImage) :
	Entity(id, x, y),
	Cactus(id, x, y, cactusImage),
	InteractableEntity(id, x, y, 0, 37, 64, 70)
{
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->cactusImage = cactusImage;
	this->stumpImage = stumpImage;
	this->destroyed = false;
	this->respawnTime = GameTimer::Instance()->getFullDayLength() * 10;
	this->interactTime = 6000;

	this->animationType = AnimationEnumType::Chop;
}

bool InteractableCactus::canInteract(Player* player) {
	if (player->getInventory()->axeSelected()) {
		this->setHighlightTexture(this->getCanInteractTexture());
	} else {
		this->setHighlightTexture(this->getCantInteractTexture());
	}
	return player->getInventory()->axeSelected();
}

void InteractableCactus::update(double dt) {
	if (this->destroyed) {
		if (this->timeDestroyed  + respawnTime < GameTimer::Instance()->getGameTime()) {
			this->respawn();
		}
	}
}

void InteractableCactus::respawn() {
	this->destroyed = false;
	this->setDrawImage(this->cactusImage);
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
}

void InteractableCactus::interact(Player* player)
{
	if (player->getInventory()->axeSelected()) {
		player->setCorrectToolSelected(true);
		InteractableEntity::interact(player);
		if (this->trackInteractTimes()) {
			player->setCorrectToolSelected(false);
			this->setDestroyedState();
			player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Water));
			this->degradeTool(player);
			//TODO: add to statustracker
			player->getStatusTracker()->addAchievementCount(AchievementsEnum::CACTUSSESEXTRACTED);
		}
	} else {
		player->setCorrectToolSelected(false);
	}
}

void InteractableCactus::setDestroyedState()
{
	this->setHighlighted(false);
	this->timeDestroyed = GameTimer::Instance()->getGameTime();
	this->destroyed = true;
	this->setDrawImage(this->stumpImage);
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	currentInteractTime = 0;
}

InteractableCactus::~InteractableCactus()
{
	PlayState::Instance()->getMainEntityContainer()->getRespawnContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
}
