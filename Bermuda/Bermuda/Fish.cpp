#include "Fish.h"
#include "PlayState.h"


Fish::Fish(int id, double x, double y, int chunkSize, Image* fishImage) :
	Entity(id,x,y,chunkSize), 
	DrawableEntity(id,x,y,chunkSize, fishImage), 
	InteractableEntity(id,x,y,chunkSize, -64, -64, 192, 192)
{
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);

	this->destroyed = false;
	this->respawnTime = 10000;
	this->interactTime = 500;

	this->timeSinceDestroy = 0;
	this->currentInteractTime = 0;
}

void Fish::interact(Player* player) {
	//if (player->getInventory()->hasAxe()) {
		//InteractableEntity::interact(player);

		//if (this->trackInteractTimes()) {
		//	this->setDestroyedState();
		//	player->getInventory()->addItem(new ItemWood());
		//	player->getStatusTracker()->treeCut();
		//}
	//}
}


Fish::~Fish()
{
}
