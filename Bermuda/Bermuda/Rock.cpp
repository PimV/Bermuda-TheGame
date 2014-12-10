#include "Rock.h"
#include "PlayState.h"
#include "Player.h"
#include "ItemFactory.h"
#include "Items.h"
#include <ctime> 

Rock::Rock(int id, double x, double y, Image* rockImage, Image* rockPiecesImage) :
	Entity(id,x,y), 
	DrawableEntity(id,x,y, rockImage), 
	CollidableEntity(id,x,y, 0, 14, 32, 18), rockImage(rockImage), rockPiecesImage(rockPiecesImage),
	InteractableEntity(id,x,y, -35, -35, this->getWidth() + 70, this->getHeight() + 70)
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->interactTime = 5000;
	this->animationType = AnimationEnumType::Mine;
}

void Rock::update(double dt) {

}

void Rock::interact(Player* player)
{
	if (player->getInventory()->pickAxeSelected()) {
		InteractableEntity::interact(player);
		player->setCorrectToolSelected(true);
		if (this->trackInteractTimes()) {
			player->setCorrectToolSelected(false);
			this->setDestroyedState();
			player->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Rock));
			//Random flint chance
			srand(time(NULL));
			int flintChance = rand() % 10 + 1;	
			if (flintChance > 9) {
				Item* flint = ItemFactory::Instance()->createItem(Items::Flint);
				flint->setStackSize(1);
				player->getInventory()->addItem(flint);
			}

			//Degradability
			Equipable* tool = dynamic_cast<Equipable*>(player->getInventory()->getSelectedItem());
			tool->setDurability(tool->getDurability() - 1);
			std::cout << tool->getPercentageDegraded() << std::endl;
			if (tool->getDurability() <= 0) {
				std::cout << "Destroying pickaxe, no durability!" << std::endl;
				player->getInventory()->deleteItem(tool->getId(), 1);
			}

			//Set rock mined
			player->getStatusTracker()->rockMined();
		}
	} else {
		player->setCorrectToolSelected(false);
	}
}

void Rock::setDestroyedState()
{
	this->destroyed = true;
	this->setCollisionX(0);
	this->setCollisionWidth(0);
	this->setCollisionY(0);
	this->setCollisionHeight(0);
	this->setDrawImage(this->rockPiecesImage);
	PlayState::Instance()->getMainEntityContainer()->getBackgroundContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
}

Rock::~Rock()
{
	PlayState::Instance()->getMainEntityContainer()->getBackgroundContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
}
