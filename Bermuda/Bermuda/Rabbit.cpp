#include "Rabbit.h"

Rabbit::Rabbit(int id, Spawnpoint* spawnPoint, int firstImgID) :
	Entity(id, spawnPoint->getX(), spawnPoint->getY()),
	InteractableNPC(id, 20, 0, 150, 0, spawnPoint, -15, -18, 68, 78, 500),
	DrawableEntity(id, spawnPoint->getX(), spawnPoint->getY(), nullptr),
	CollidableEntity(id, spawnPoint->getX(), spawnPoint->getY(), 4, 20, 28, 12),
	MovableEntity(id, spawnPoint->getX(), spawnPoint->getY())
{
	this->setWidth(36);
	this->setHeight(36);

	#pragma region Moving_stuff
	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 2;
	this->moveSpeed = 2;
	this->stopSpeed = 0.8;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	#pragma endregion

	this->healthPoints = 20;
	this->attackPoints = 0;
	this->actionRange = 150;
	this->attackRange = 0;

	#pragma region Animation_stuff
	this->firstImgID = firstImgID;
	this->animationWalkUpRow = 1, this->animationWalkLeftRow = 3;
	this->animationWalkDownRow = 0, this->animationWalkRightRow = 2;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; this->animationWalkStartColumn = 1, this->animationWalkEndColumn = 7;

	this->frameAmountX = 8, this->frameAmountY = 4, this->CurrentFrame = 0;
	this->animationSpeed = 10;
	#pragma endregion
	
	#pragma region Interactable_stuff
	this->interactTime = 500;
	this->currentInteractTime = 0;
	this->animationType = AnimationEnumType::Attack;
	#pragma endregion

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);

	this->StopAnimation();

	this->behaviour = new EvasiveBehaviour( new StateMachine<Entity>(this) );
}

void Rabbit::update(double dt)
{
	if (this->getHealthPoints() > 0)
	{
		this->behaviour->update(dt);
	}
	else
	{
		this->setDestroyedState();
	}
}

void Rabbit::interact(Player* player)
{
	if (player->getInventory()->getSelectedItem()->hasItemType(ItemType::Weapon))
	{
		player->setCorrectToolSelected(true);
		InteractableEntity::interact(player);

		if (this->trackInteractTimes())
		{
			player->setCorrectToolSelected(false);
			this->currentInteractTime = 0;
			this->setHealthPoints( this->getHealthPoints() - dynamic_cast<class Weapon*>(player->getInventory()->getSelectedItem())->getAttackDamage() );
		}
	}
	else
	{
		player->setCorrectToolSelected(false);
	}
}

void Rabbit::setDestroyedState() 
{
	PlayState::Instance()->getPlayer()->getStatusTracker()->RabbitsKilled();
	PlayState::Instance()->getPlayer()->getInventory()->addItem(ItemFactory::Instance()->createItem(Items::Meat));
	this->getSpawnPoint()->decreaseChildren();
	PlayState::Instance()->getMainEntityContainer()->getDestroyContainer()->add(this);
}

void Rabbit::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Rabbit::ResetDrawableEntityAndSetChunk()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	this->setChunks(); 
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->add(this);
}

bool Rabbit::checkCollision(double newX, double newY)
{
	return CollidableEntity::checkCollision(newX, newY);
}

Rabbit::~Rabbit()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
}
