#include "Player.h"
#include "header_loader.h"
#include "GameOverState.h"
#include <iostream>
#include "Inventory.h"
#include "PlayState.h"

Player::Player(int id, double moveSpeed, double x, double y, int chunkSize, Camera* camera)
	: Entity(id,x,y,chunkSize), DrawableEntity(id,x,y,chunkSize, nullptr), CollidableEntity(id,x,y,chunkSize, 20, 52, 24, 10), MovableEntity(id, x, y, chunkSize)
{
	healthBar = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "HealthBar.png").c_str());
	healthBarContainer = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "HealthBarContainerBas.png").c_str());

	hungerBar = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Hungerbar.png").c_str());
	hungerBarContainer = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "HungerBarContainerBas.png").c_str());

	thirstBar = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "ThirstBar.png").c_str());
	thirstBarContainer = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "ThirstBarContainerBas.png").c_str());


	this->camera = camera;

	//Entity -> dimension values
	this->setWidth(64);
	this->setHeight(64);

	//this->playerTimer = new PlayerUpdateTimer();
	this->hungerUpdate = 0; this->hungerUpdateTime = 2200;
	this->thirstUpdate = 0; this->thirstUpdateTime = 1500;
	this->health = 100; this->hunger = 100; this->thirst = 100;

	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 3;
	this->moveSpeed = 3;
	this->sprinting = false;
	this->sprintSpeed = 15;

	this->setTempX(this->getX());
	this->setTempY(this->getY());

	this->stopSpeed = 0.8;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	this->moveClick = false;
	this->interaction = false;

	this->firstImgID = GameStateManager::Instance()->getImageLoader()->loadTileset("Player_Dagger.png", 64, 64);
	this->animationWalkUpRow = 8, this->animationWalkLeftRow = 9;
	this->animationWalkDownRow = 10, this->animationWalkRightRow = 11;
	this->currentAnimationRow = this->animationWalkDownRow;
	this->animationIdleColumn = 0; this->animationWalkStartColumn = 1, this->animationWalkEndColumn = 8;
	this->animationActionStartColumn = 1; this->animationActionEndColumn = 5;
	this->frameAmountX = 13, this->frameAmountY = 21, this->CurrentFrame = 0;
	this->animationSpeed = 10;//, this->animationDelay = 1;

	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));

	this->StopAnimation();

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);

	this->inventory = new Inventory();
	this->statusTracker = new StatusTracker();
}

Inventory* Player::getInventory() {
	return this->inventory;
}

StatusTracker* Player::getStatusTracker()
{
	return this->statusTracker;
}

void Player::resetMovement() {
	if (this->moveClick) {
		this->movingLeft = false;
		this->movingRight = false;
		this->movingDown = false;
		this->movingUp = false;
		this->moveClick = false;
		StopAnimation();
	}
}

void Player::update(double dt) {
	// check if player died
	if (this->getHealth() < 1)
	{
		GameStateManager::Instance()->changeGameState(GameOverState::Instance());
		return;
	}

	this->updatePlayerStatuses(dt);
	this->directionsAndMove(dt);

	//ROELS CODE HIERONDER TIJDELIJK UITGEZET
	/*if (interaction)
	{
	interact(dt);
	}
	else
	{
	this->move(dt);
	}*/
}

#pragma region PlayerStatusUpdates
void Player::updatePlayerStatuses(double dt)
{

	// check if hunger needs to be updated
	this->hungerUpdate += GameStateManager::Instance()->getUpdateLength() * dt;// * dt;
	if (this->hungerUpdate > hungerUpdateTime) {
		this->setHunger(this->getHunger() - 1);
		if (this->getHunger() <= 0) {
			this->setHealth(this->getHealth() - 1);
		}
		hungerUpdate = 0;
	}

	// check if thirst needs to be updated
	this->thirstUpdate += GameStateManager::Instance()->getUpdateLength() * dt;// * dt;
	if (this->thirstUpdate > thirstUpdateTime) {
		this->setThirst(this->getThirst() - 1);
		if (this->getThirst() <= 0) {
			this->setHealth(this->getHealth() - 1);
		}
		thirstUpdate = 0;
	}
}

void Player::incrementHealth(int value)
{
	if (this->getHealth() + value > 100) {
		this->setHealth(100);
	} else if (this->getHealth() + value < 0) {
		this->setHealth(0);
	} else {
		this->setHealth(this->getHealth() + value);
	}
}

void Player::incrementHunger(int value)
{
	if (this->getHunger()+value > 100) {
		this->setHunger(100);
	} else if (this->getHunger() + value < 0) {
		this->setHunger(0);
		this->setHealth(this->getHealth() + value);
	} else {
		this->setHunger(this->getHunger() + value);
	}
}

void Player::incrementThirst(int value)
{
	if (this->getThirst()+value > 100) {
		this->setThirst(100);
	} else if (this->getThirst() < 0) {
		this->setThirst(0);
		this->setHealth(this->getHealth() + value);
	} else {
		this->setThirst(this->getThirst() + value);
	}
}

void Player::setHealth(int value) {

	if (value > 100) {
		this->health = 100;
	} else if (value < 0 ) {
		this->health = 0;
	} else {
		this->health = value;
	}
}

void Player::setHunger(int value) {
	if (value > 100) {
		this->hunger = 100;
	} else if (value < 0 ) {
		this->hunger = 0;
	} else {
		this->hunger = value;
	}
}

void Player::setThirst(int value) {
	if (value > 100) {
		this->thirst = 100;
	} else if (value < 0 ) {
		this->thirst = 0;
	} else {
		this->thirst = value;
	}
}


int Player::getHealth() {
	return this->health;
}

int Player::getHunger() {
	return this->hunger;
}

int Player::getThirst() {
	return this->thirst;
}
#pragma endregion PlayerStatusUpdates

void Player::directionsAndMove(double dt)
{
	if (sprinting) {
		moveSpeed = 50;
	}
	else {
		moveSpeed = 3;
	}

	if (moveClick) {
		clickMove();
	}

	this->move(dt);
}

void::Player::interact()
{
	//Calculate begin and end chunks for the player collision (+1 and -1 to make it a little bigger thent he current chunk)
	int beginChunkX = this->getChunkX() - 1;
	int endChunkX = this->getChunkX() + 1;
	int beginChunkY = this->getChunkY() - 1;
	int endChunkY = this->getChunkY() + 1;

	int playerOffsetX = this->getX() + (this->getWidth() / 2);
	//De -7 wordt gebruikt omdat het plaatje niet helemaal klopt. In de breedte staat de speler idd precies in het midden van het plaatje. In de hoogte niet...
	int playerOffsetY = this->getY() + (this->getHeight() / 2) +7;

	double diff = 1000;
	InteractableEntity* closestEntity = nullptr;

	//Loop through all chunks
	for(int i = beginChunkY; i <= endChunkY; i++) {
		for(int j = beginChunkX; j <= endChunkX; j++) {
			std::vector<InteractableEntity*>* vec = PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->getChunk(i, j);
			if(vec != nullptr) {

				for(InteractableEntity* e : *vec) {
					if((playerOffsetX >= (e->getX() + e->getInteractStartX()) && (playerOffsetX <= (e->getX() + e->getInteractStartX() + e->getInteractWidth()))) && 
						(playerOffsetY >= (e->getY() + e->getInteractStartY()) && playerOffsetY <= (e->getY() + e->getInteractStartY() + e->getInteractHeight())))
					{
						double centerX = ((e->getX() + e->getInteractStartX()) + (e->getX() + e->getInteractStartX() + e->getInteractWidth())) /2;
						double centerY = ((e->getY() + e->getInteractStartY()) + (e->getY() + e->getInteractStartY() + e->getInteractHeight())) / 2;

						double diffX = centerX - playerOffsetX;
						double diffY = centerY - playerOffsetY;

						if (diffX < 0) {
							diffX = -diffX;
						}

						if (diffY < 0) {
							diffY = -diffY;
						}

						if (diffX + diffY < diff) {
							diff = diffX + diffY;
							closestEntity = e;
						}

						//e->interact(this);
						//TODO : juiste animatie laten zien e.d.
						//break;
					}
				}
			}
		}
	}

	if (closestEntity != nullptr) {
		closestEntity->interact(this);
	}

	//ROELS CODE HIERONDER UITGEZET, ANIMATIE IS AFHANKELIJK VAN WAARMEE GEINTERACT WORDT??????
	//// this is for setting the new animation, the value only needs to be added once
	//if (this->currentPlayerAnimationRow == this->playerAnimationWalkUpRow)
	//	this->currentPlayerAnimationRow += 4;
	//else if (this->currentPlayerAnimationRow == this->playerAnimationWalkLeftRow)
	//	this->currentPlayerAnimationRow += 4;
	//else if (this->currentPlayerAnimationRow == this->playerAnimationWalkDownRow)
	//	this->currentPlayerAnimationRow += 4;
	//else if (this->currentPlayerAnimationRow == this->playerAnimationWalkRightRow)
	//	this->currentPlayerAnimationRow += 4;

	//this->PlayAnimation(this->playerAnimationActionStartColumn, this->playerAnimationActionEndColumn, this->currentPlayerAnimationRow, dt);
}

void Player::setPosition() {
	MovableEntity::setPosition();

	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));
}

double Player::getDistence(int currentX, int currentY, int destX, int destY)
{
	double DifferenceX = currentX - destX;
	double DifferenceY = currentY - destY;
	return sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
}

void Player::clickMove() {

	if (this->getX() + this->getWidth() / 2 > this->destX - 5 && this->getX() + this->getWidth() / 2  < this->destX + 5) {
		movingRight = false;
		movingLeft = false;
	} else if(this->destX > this->getX() + this->getWidth() / 2)
	{
		movingRight = true;
		movingLeft = false;
	}
	else if(this->destX < this->getX() + this->getWidth() / 2)
	{
		movingLeft = true;
		movingRight = false;
	}

	if (this->getY() + this->getHeight() > this->destY - 5 && this->getY() + this->getHeight() < this->destY + 5) {
		movingDown = false;
		movingUp = false;
	} else if(this->destY > this->getY() + this->getHeight())
	{
		movingDown = true;
		movingUp = false;
	}
	else if(this->destY < this->getY() + this->getHeight())
	{
		movingUp = true;
		movingDown = false;
	}

	if (!movingDown && !movingUp && !movingLeft && !movingRight) {
		moveClick = false;
	}
}

void Player::setImage(Image* image)
{
	this->setDrawImage(image);
}

void Player::ResetDrawableEntityAndSetChunk()
{
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);
	this->setChunks(); 
	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);
}

bool Player::checkIntersects(CollidableEntity* collidableEntity)
{
	return this->intersects(collidableEntity, this);
}

void Player::drawHealthBar(int x, int y) {
	SDL_Rect healthContainerRect;
	healthContainerRect.h = 16;
	healthContainerRect.w = (this->getInventory()->getWidth() / 5);
	healthContainerRect.x = x;
	healthContainerRect.y = y;
	GameStateManager::Instance()->sdlInitializer->drawTexture(healthBarContainer,&healthContainerRect,NULL);


	SDL_Rect healthRect;
	healthRect.h = 14;
	healthRect.w = 2*(this->getInventory()->getWidth() / 10) * this->getHealth() / 100;
	healthRect.x = x + 1;
	healthRect.y = y + 1;
	GameStateManager::Instance()->sdlInitializer->drawTexture(healthBar,&healthRect,NULL);
	GameStateManager::Instance()->sdlInitializer->drawText(std::to_string(this->getHealth()), x + (this->getInventory()->getWidth() / 5) / 2 - 10, y, 20, 18);
	GameStateManager::Instance()->sdlInitializer->drawText(std::string("HEALTH:"), x , y - 24, 30, 24);
}

void Player::drawHungerBar(int x, int y) {
	SDL_Rect hungerContainerRect;
	hungerContainerRect.h = 16;
	hungerContainerRect.w = (this->getInventory()->getWidth() / 5);
	hungerContainerRect.x = x;
	hungerContainerRect.y = y;
	GameStateManager::Instance()->sdlInitializer->drawTexture(hungerBarContainer,&hungerContainerRect,NULL);


	SDL_Rect hungerRect;
	hungerRect.h = 14;
	hungerRect.w = (this->getInventory()->getWidth() / 5) * this->getHunger() / 100;
	hungerRect.x = x + 1;
	hungerRect.y = y + 1;
	GameStateManager::Instance()->sdlInitializer->drawTexture(hungerBar,&hungerRect,NULL);
	GameStateManager::Instance()->sdlInitializer->drawText(std::to_string(this->getHunger()), x + (this->getInventory()->getWidth() / 5) / 2 - 10, y, 15, 18);
	GameStateManager::Instance()->sdlInitializer->drawText(std::string("HUNGER:"), x , y - 24, 30, 24);
}

void Player::drawThirstBar(int x, int y) {
	SDL_Rect thirstContainerRect;
	thirstContainerRect.h = 16;
	thirstContainerRect.w = (this->getInventory()->getWidth() / 5);
	thirstContainerRect.x = x;
	thirstContainerRect.y = y;
	GameStateManager::Instance()->sdlInitializer->drawTexture(thirstBarContainer,&thirstContainerRect,NULL);

	SDL_Rect thirstRect;
	thirstRect.h = 14;
	thirstRect.w = (this->getInventory()->getWidth() / 5) * this->getThirst() / 100;
	thirstRect.x = x + 1;
	thirstRect.y = y + 1;
	GameStateManager::Instance()->sdlInitializer->drawTexture(thirstBar,&thirstRect,NULL);
	GameStateManager::Instance()->sdlInitializer->drawText(std::to_string(this->getThirst()), x + (this->getInventory()->getWidth() / 5) / 2 - 10, y, 15, 18);
	GameStateManager::Instance()->sdlInitializer->drawText(std::string("THIRST:"), x , y - 24, 30, 24);
}


void Player::draw() {
	this->drawHealthBar(this->getInventory()->getStartingX(), this->getInventory()->getStartingY() - 30);

	this->drawThirstBar(this->getInventory()->getStartingX() + 2*((this->getInventory()->getWidth()) / 5), this->getInventory()->getStartingY() - 30);

	this->drawHungerBar(this->getInventory()->getStartingX() + 4*((this->getInventory()->getWidth())/ 5), this->getInventory()->getStartingY() - 30);
}

Player::~Player(void) {
	delete this->inventory;
	delete this->statusTracker;
}
