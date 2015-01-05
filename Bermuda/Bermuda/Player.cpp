#include "Player.h"
#include "GameOverState.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "Item.h"
#include <vector>

Player::Player(int id, double moveSpeed, double x, double y, Camera* camera) : 
	Entity(id, x, y),
	DrawableEntity(id, x, y, nullptr),
	CollidableEntity(id, x, y, 20, 52, 24, 10),
	MovableEntity(id, x, y)
{
	healthBar = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "HealthBar.png").c_str());
	healthBarContainer = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "HealthBarContainerBas.png").c_str());

	hungerBar = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Hungerbar.png").c_str());
	hungerBarContainer = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "HungerBarContainerBas.png").c_str());

	thirstBar = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "ThirstBar.png").c_str());
	thirstBarContainer = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "ThirstBarContainerBas.png").c_str());

	SDL_SetTextureBlendMode(hungerBar, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(hungerBarContainer, SDL_BLENDMODE_BLEND);

	SDL_SetTextureBlendMode(healthBar, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(healthBarContainer, SDL_BLENDMODE_BLEND);

	SDL_SetTextureBlendMode(thirstBar, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(thirstBarContainer, SDL_BLENDMODE_BLEND);

	healthAlphaFade = true;
	hungerAlphaFade = true;
	thirstAlphaFade = true;

	healthAlpha = 255;
	hungerAlpha = 255;
	thirstAlpha = 255;

	godMode = false;

	this->camera = camera;

	//Entity -> dimension values
	this->setWidth(64);
	this->setHeight(64);

	//this->playerTimer = new PlayerUpdateTimer();
	this->hungerUpdate = GameTimer::Instance()->getGameTime(); 
	this->thirstUpdate = GameTimer::Instance()->getGameTime();
	this->healthUpdate = GameTimer::Instance()->getGameTime();
	this->darknessUpdate = GameTimer::Instance()->getGameTime();
	this->quickDeathUpdate = GameTimer::Instance()->getGameTime();
	this->hungerUpdateTime = 6000;
	this->thirstUpdateTime = 5000;
	this->healthUpdateTime = 1500;
	this->darknessUpdateTime = 3500; 
	this->quickDeathUpdateTime = 50; // increase to die faster when not in the light
	this->health = 100; 
	this->hunger = 100; 
	this->thirst = 100;
	this->withinDarkness = false;

	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 3;
	this->moveSpeed = 3;
	this->sprinting = false;
	this->sprintSpeed = 15;

	this->stopSpeed = 0.8;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	this->moveClick = false;
	this->interaction = false;

	this->firstImgID = PlayState::Instance()->getImageLoader()->loadTileset("Player_Animations.png", 64, 64);

	#pragma region animation
	this->animationWalkUpRow = 4;
	this->animationWalkLeftRow = 5;
	this->animationWalkDownRow = 6;
	this->animationWalkRightRow = 7;
	this->animationWalkStartColumn = 1;
	this->animationWalkEndColumn = 8;

	this->animationSpearWalkUp = 8;
	this->animationSpearWalkLeft = 9;
	this->animationSpearWalkDown = 10;
	this->animationSpearWalkRight = 11;
	this->animationSpearWalkStartColumn = 1;
	this->animationSpearWalkEndColumn = 8;
	
	this->animationPickUp = 0;
	this->animationPickStartColumn = 1;
	this->animationPickEndColumn = 6;

	this->animationChopUp = 12;
	this->animationChopStartColumn = 1;
	this->animationChopEndColumn = 9;

	this->animationChopGoldUp = 16;
	this->animationChopGoldStartColumn = 1;
	this->animationChopGoldEndColumn = 9;

	this->animationMineUp = 20;
	this->animationMineStartColumn = 1;
	this->animationMineEndColumn = 9;

	this->animationMineGoldUp = 24;
	this->animationMineGoldStartColumn = 1;
	this->animationMineGoldEndColumn = 9;

	this->animationSpearAttackUp = 28;
	this->animationSpearAttackStartColumn = 1;
	this->animationSpearAttackEndColumn = 9;

	this->movementDirection = MovementDirectionEnum::Down;
	this->currentAnimationRow = (this->animationWalkUpRow + (int)this->movementDirection);

	this->animationIdleColumn = 0;
	this->animationActionStartColumn = 1; this->animationActionEndColumn = 5;

	this->frameAmountX = 13, this->frameAmountY = 27, this->CurrentFrame = 0;
	this->animationSpeed = 10;//, this->animationDelay = 1;

	this->defaultAnimationSpeed = 40;
	this->defaultAnimationActionSpeed = 50;
	#pragma endregion animation

	this->correctToolSelected = false;

	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));

	this->StopAnimation();

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->add(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->add(this);

	this->inventory = new Inventory();
	this->crafting = new Crafting(this->inventory);
	this->statusTracker = new StatusTracker();
}

void Player::toggleGodMode() {
	this->godMode = !this->godMode;
}

Inventory* Player::getInventory() {
	return this->inventory;
}

Crafting* Player::getCraftingSystem()
{
	return this->crafting;
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
		this->StopAnimation();
	}
}

void Player::update(double dt) {
	// check if player died
	if (this->getHealth() < 1)
	{
		PlayState::Instance()->setGameOver(true);
		return;
	}

	if (!this->godMode) {
	this->changeAnimationOnInventorySelection();

	this->updatePlayerStatuses(dt);
	}

	if (this->interaction) {
		this->interact(dt);
	}
	else {
		this->directionsAndMove(dt);
	}

}

#pragma region PlayerStatusUpdates
void Player::updatePlayerStatuses(double dt)
{
	long currentTime = GameTimer::Instance()->getGameTime();

	// check if hunger needs to be updated
	if (this->hungerUpdate + this->hungerUpdateTime < currentTime) {
		this->setHunger(this->getHunger() - 1);
	}

	// check if thirst needs to be updated
	if (this->thirstUpdate + this->thirstUpdateTime < currentTime) {
		this->setThirst(this->getThirst() - 1);
	}

	//this->healthUpdate += GameStateManager::Instance()->getUpdateLength() * dt;
	if (this->healthUpdate + this->healthUpdateTime < currentTime) {
		if (this->getThirst() > 80 && this->getHunger() > 80) {
			this->setHealth(this->getHealth() + 2);
		}
		else if (this->getThirst() > 40 && this->getHunger() > 40) {
			this->setHealth(this->getHealth() + 1);
		}
		else if (this->getThirst() <= 0 && this->getHunger() <= 0)
		{
			this->setHealth(this->getHealth() - 4);
		}
		else if (this->getThirst() <= 0 || this->getHunger() <= 0)
		{
			this->setHealth(this->getHealth() - 2);
		}
	}

	if (this->withinDarkness == true)
	{
		if (this->darknessUpdate + this->darknessUpdateTime < currentTime) 
		{
			if (this->quickDeathUpdate + this->quickDeathUpdateTime < currentTime)
			{
				this->setHealth(this->getHealth() - 1);
				this->quickDeathUpdate = currentTime;
}
		}
	}
	else
	{
		this->darknessUpdate = currentTime;
	}

}

void Player::incrementHealth(int value)
{
	if (this->getHealth() + value > 100) {
		this->setHealth(100);
	}
	else if (this->getHealth() + value < 0) {
		this->setHealth(0);
	}
	else {
		this->setHealth(this->getHealth() + value);
	}
}

void Player::incrementHunger(int value)
{
	if (this->getHunger() + value > 100) {
		this->setHunger(100);
	}
	else if (this->getHunger() + value < 0) {
		this->setHunger(0);
		this->setHealth(this->getHealth() + value);
	}
	else {
		this->setHunger(this->getHunger() + value);
	}
}

void Player::incrementThirst(int value)
{
	if (this->getThirst() + value > 100) {
		this->setThirst(100);
	}
	else if (this->getThirst() < 0) {
		this->setThirst(0);
		this->setHealth(this->getHealth() + value);
	}
	else {
		this->setThirst(this->getThirst() + value);
	}
}

void Player::setHealth(int value) {

	if (value > 100) {
		this->health = 100;
	}
	else if (value < 0) {
		this->health = 0;
	}
	else {
		this->health = value;
	}
	this->healthUpdate = GameTimer::Instance()->getGameTime();
}

void Player::setHunger(int value) {
	if (value > 100) {
		this->hunger = 100;
	}
	else if (value < 0) {
		this->hunger = 0;
	}
	else {
		this->hunger = value;
	}
	this->hungerUpdate = GameTimer::Instance()->getGameTime();
}

void Player::setThirst(int value) {
	if (value > 100) {
		this->thirst = 100;
	}
	else if (value < 0) {
		this->thirst = 0;
	}
	else {
		this->thirst = value;
	}
	this->thirstUpdate = GameTimer::Instance()->getGameTime();
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

void::Player::interact(double dt)
{
	//Calculate begin and end chunks for the interact check (+1 and -1 to make it a little bigger thent he current chunk)
	int beginChunkX = this->getChunkX() - 1;
	int endChunkX = this->getChunkX() + 1;
	int beginChunkY = this->getChunkY() - 1;
	int endChunkY = this->getChunkY() + 1;

	int playerOffsetX = this->getX() + (this->getWidth() / 2);
	//De -7 wordt gebruikt omdat het plaatje niet helemaal klopt. In de breedte staat de speler idd precies in het midden van het plaatje. In de hoogte niet...
	int playerOffsetY = this->getY() + (this->getHeight() / 2) + 7;

	double diff = 1000;
	InteractableEntity* closestEntity = nullptr;

	//Loop through all chunks
	for (int i = beginChunkY; i <= endChunkY; i++) {
		for (int j = beginChunkX; j <= endChunkX; j++) {
			std::vector<InteractableEntity*>* vec = PlayState::Instance()->getMainEntityContainer()->getInteractableContainer()->getChunk(i, j);
			if (vec != nullptr) {

				for (InteractableEntity* e : *vec) {
					if ((playerOffsetX >= (e->getX() + e->getInteractStartX()) && (playerOffsetX <= (e->getX() + e->getInteractStartX() + e->getInteractWidth()))) &&
						(playerOffsetY >= (e->getY() + e->getInteractStartY()) && playerOffsetY <= (e->getY() + e->getInteractStartY() + e->getInteractHeight())))
					{
						double centerX = ((e->getX() + e->getInteractStartX()) + (e->getX() + e->getInteractStartX() + e->getInteractWidth())) / 2;
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

					}
				}
			}
		}
	}

	if (closestEntity != nullptr) {
		// execure interate first, for it is needed to get the correct animation
		closestEntity->interact(this);

		// set and play animation
		if (closestEntity->getAnimationEnumType() != AnimationEnumType::None && this->getCorrectToolSelected()) {
			this->setAnimationType(closestEntity->getAnimationEnumType());
			this->PlayAnimation(this->animationActionStartColumn, this->animationActionEndColumn, this->currentAnimationRow, dt, this->defaultAnimationActionSpeed);
		}
	}
}

void Player::setAnimationType(AnimationEnumType type)
{
	switch (type)
	{
	case AnimationEnumType::None:
		std::cout << "Animation type is None" << std::endl;
		break;
	case AnimationEnumType::Chop:
		switch(this->getInventory()->getSelectedItem()->getId())
		{
		case (int)Items::Axe:
			this->currentAnimationRow = this->animationChopUp + (int)this->movementDirection;
 			this->animationActionStartColumn = this->animationChopStartColumn;
			this->animationActionEndColumn = this->animationChopEndColumn;
			break;
		case (int)Items::GoldenAxe:
			this->currentAnimationRow = this->animationChopGoldUp + (int)this->movementDirection;
 			this->animationActionStartColumn = this->animationChopGoldStartColumn;
			this->animationActionEndColumn = this->animationChopGoldEndColumn;
			break;
		}
		break;
	case AnimationEnumType::Mine:
		switch(this->getInventory()->getSelectedItem()->getId())
		{
		case (int)Items::Pickaxe:
			this->currentAnimationRow = this->animationMineUp + (int)this->movementDirection;
 			this->animationActionStartColumn = this->animationMineStartColumn;
			this->animationActionEndColumn = this->animationMineEndColumn;
			break;			
		case (int)Items::GoldenPickaxe:
			this->currentAnimationRow = this->animationMineGoldUp + (int)this->movementDirection;
 			this->animationActionStartColumn = this->animationMineGoldStartColumn;
			this->animationActionEndColumn = this->animationMineGoldEndColumn;
			break;
		}
		break;
	case AnimationEnumType::Pick:
			this->currentAnimationRow = this->animationPickUp + (int)this->movementDirection;
 			this->animationActionStartColumn = this->animationPickStartColumn;
			this->animationActionEndColumn = this->animationPickEndColumn;
		break;
	case AnimationEnumType::AttackSpear:
			this->currentAnimationRow = this->animationSpearAttackUp + (int)this->movementDirection;
			this->animationActionStartColumn = this->animationSpearAttackStartColumn;
			this->animationActionEndColumn = this->animationSpearAttackEndColumn;
		break;
	default:
		break;
	}
}

void Player::changeAnimationOnInventorySelection()
{
	// fugly, might be an good idae to redo the animation selection
	if (this->getInventory()->spearSelected())
	{
		// only one check is necessary, for all the walkAnimation needs to be changed if Spear is selected
		if (this->animationWalkUpRow != this->animationSpearWalkUp)
		{
			// set the movementAnimation to the movementSpearAnimation
			this->animationWalkUpRow = this->animationSpearWalkUp;
			this->animationWalkLeftRow = this->animationSpearWalkLeft;
			this->animationWalkDownRow = this->animationSpearWalkDown;
			this->animationWalkRightRow = this->animationSpearWalkRight;
			this->animationWalkStartColumn = this->animationSpearWalkStartColumn;
			this->animationWalkEndColumn = this->animationSpearWalkEndColumn;
			this->currentAnimationRow = this->animationSpearWalkUp + (int)this->movementDirection;
			this->StopAnimation();
		}
	}
	else
	{
		if (this->animationWalkUpRow != 4)
		{
			// reset the movementAnimation to the correct values
			this->animationWalkUpRow = 4;
			this->animationWalkLeftRow = 5;
			this->animationWalkDownRow = 6;
			this->animationWalkRightRow = 7;
			this->animationWalkStartColumn = 1;
			this->animationWalkEndColumn = 8;
			this->currentAnimationRow = this->animationWalkUpRow + (int)this->movementDirection;
			this->StopAnimation();
		}
	}
}

void Player::setPosition(double newX, double newY) {
	MovableEntity::setPosition(newX, newY);

	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));
}

double Player::getDistance(int currentX, int currentY, int destX, int destY)
{
	double DifferenceX = currentX - destX;
	double DifferenceY = currentY - destY;
	return sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
}

void Player::clickMove() {

	if (this->getX() + this->getWidth() / 2 > this->destX - 5 && this->getX() + this->getWidth() / 2 < this->destX + 5) {
		movingRight = false;
		movingLeft = false;
	}
	else if (this->destX > this->getX() + this->getWidth() / 2)
	{
		movingRight = true;
		movingLeft = false;
	}
	else if (this->destX < this->getX() + this->getWidth() / 2)
	{
		movingLeft = true;
		movingRight = false;
	}

	if (this->getY() + this->getHeight() > this->destY - 5 && this->getY() + this->getHeight() < this->destY + 5) {
		movingDown = false;
		movingUp = false;
	}
	else if (this->destY > this->getY() + this->getHeight())
	{
		movingDown = true;
		movingUp = false;
	}
	else if (this->destY < this->getY() + this->getHeight())
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

bool Player::checkCollision(double newX, double newY)
{
	return CollidableEntity::checkCollision(newX, newY);
}

bool Player::getCorrectToolSelected()
{
	return this->correctToolSelected;
}

void Player::setCorrectToolSelected(bool tool)
{
	this->correctToolSelected = tool;
}

void Player::drawHealthBar(int x, int y) {
	if (this->getHealth() < 30) {
		if (healthAlpha < 30) {
			healthAlphaFade = false;
		}

		if (healthAlphaFade == true) {
			healthAlpha = healthAlpha - (40 - this->getHealth());
			if (healthAlpha < 0) {
				healthAlphaFade = false;
				healthAlpha = 0;
			}
		}
		else {
			healthAlpha = healthAlpha + (40 - this->getHealth());
			if (healthAlpha > 255) {
				healthAlphaFade = true;
				healthAlpha = 255;
			}

		}
		SDL_SetTextureAlphaMod(healthBar, healthAlpha);
		SDL_SetTextureAlphaMod(healthBarContainer, healthAlpha);

	}
	else {
		if (healthAlpha != 255) {

			healthAlpha = 255;
			healthAlphaFade = true;
			SDL_SetTextureAlphaMod(healthBar, healthAlpha);
			SDL_SetTextureAlphaMod(healthBarContainer, healthAlpha);
		}
	}

	SDL_Rect healthContainerRect;
	healthContainerRect.h = 20;
	healthContainerRect.w = 3 * (this->getInventory()->getWidth() / 10);
	healthContainerRect.x = x;
	healthContainerRect.y = y;
	GameStateManager::Instance()->sdlInitializer->drawTexture(healthBarContainer, &healthContainerRect, NULL);


	SDL_Rect healthRect;
	healthRect.h = 18;
	healthRect.w = 3 * (this->getInventory()->getWidth() / 10) * this->getHealth() / 100;
	healthRect.x = x + 1;
	healthRect.y = y + 1;
	GameStateManager::Instance()->sdlInitializer->drawTexture(healthBar, &healthRect, NULL);
	GameStateManager::Instance()->sdlInitializer->drawText(std::to_string(this->getHealth()), x + 3 * (this->getInventory()->getWidth() / 10) / 2 - 10, y, 20, 18);
	if (GameStateManager::Instance()->helpEnabled()) {
		GameStateManager::Instance()->sdlInitializer->drawText(std::string("HEALTH:"), x, y - 24, 30, 24);
	}
}

void Player::drawHungerBar(int x, int y) {
	if (this->getHunger() < 30) {
		if (hungerAlpha < 30) {
			hungerAlphaFade = false;
		}

		if (hungerAlphaFade == true) {
			hungerAlpha = hungerAlpha - (40 - this->getHunger());
			if (hungerAlpha < 0) {
				hungerAlphaFade = false;
				hungerAlpha = 0;
			}
		}
		else {
			hungerAlpha = hungerAlpha + (40 - this->getHunger());
			if (hungerAlpha > 255) {
				hungerAlphaFade = true;
				hungerAlpha = 255;
			}

		}
		SDL_SetTextureAlphaMod(hungerBar, hungerAlpha);
		SDL_SetTextureAlphaMod(hungerBarContainer, hungerAlpha);
	}
	else {
		if (hungerAlpha != 255) {

			hungerAlpha = 255;
			hungerAlphaFade = true;
			SDL_SetTextureAlphaMod(hungerBar, hungerAlpha);
			SDL_SetTextureAlphaMod(hungerBarContainer, hungerAlpha);
		}
	}

	SDL_Rect hungerContainerRect;
	hungerContainerRect.h = 20;
	hungerContainerRect.w = 3 * (this->getInventory()->getWidth() / 10);
	hungerContainerRect.x = x;
	hungerContainerRect.y = y;
	GameStateManager::Instance()->sdlInitializer->drawTexture(hungerBarContainer, &hungerContainerRect, NULL);

	SDL_Rect hungerRect;
	hungerRect.h = 18;
	hungerRect.w = 3 * (this->getInventory()->getWidth() / 10) * this->getHunger() / 100;
	hungerRect.x = x + 1;
	hungerRect.y = y + 1;
	GameStateManager::Instance()->sdlInitializer->drawTexture(hungerBar, &hungerRect, NULL);
	GameStateManager::Instance()->sdlInitializer->drawText(std::to_string(this->getHunger()), x + 3 * (this->getInventory()->getWidth() / 10) / 2 - 10, y, 15, 18);
	if (GameStateManager::Instance()->helpEnabled()) {
		GameStateManager::Instance()->sdlInitializer->drawText(std::string("FOOD:"), x, y - 24, 30, 24);
	}

}

void Player::drawThirstBar(int x, int y) {
	if (this->getThirst() < 30) {
		if (thirstAlpha < 30) {
			thirstAlphaFade = false;
		}

		if (thirstAlphaFade == true) {
			thirstAlpha = thirstAlpha - (40 - this->getThirst());
			if (thirstAlpha < 0) {
				thirstAlphaFade = false;
				thirstAlpha = 0;
			}
		}
		else {
			thirstAlpha = thirstAlpha + (40 - this->getThirst());
			if (thirstAlpha > 255) {
				thirstAlphaFade = true;
				thirstAlpha = 255;
			}

		}
		SDL_SetTextureAlphaMod(thirstBar, thirstAlpha);
		SDL_SetTextureAlphaMod(thirstBarContainer, thirstAlpha);

	}
	else {
		if (thirstAlpha != 255) {

			thirstAlpha = 255;
			thirstAlphaFade = true;
			SDL_SetTextureAlphaMod(thirstBar, thirstAlpha);
			SDL_SetTextureAlphaMod(thirstBarContainer, thirstAlpha);
		}
	}


	SDL_Rect thirstContainerRect;
	thirstContainerRect.h = 20;
	thirstContainerRect.w = 3 * (this->getInventory()->getWidth() / 10);
	thirstContainerRect.x = x;
	thirstContainerRect.y = y;
	GameStateManager::Instance()->sdlInitializer->drawTexture(thirstBarContainer, &thirstContainerRect, NULL);

	SDL_Rect thirstRect;
	thirstRect.h = 18;
	thirstRect.w = 3 * (this->getInventory()->getWidth() / 10) * this->getThirst() / 100;
	thirstRect.x = x + 1;
	thirstRect.y = y + 1;
	GameStateManager::Instance()->sdlInitializer->drawTexture(thirstBar, &thirstRect, NULL);
	GameStateManager::Instance()->sdlInitializer->drawText(std::to_string(this->getThirst()), x + 3 * (this->getInventory()->getWidth() / 10) / 2 - 10, y, 20, 18);
	if (GameStateManager::Instance()->helpEnabled()) {
		GameStateManager::Instance()->sdlInitializer->drawText(std::string("WATER:"), x, y - 24, 30, 24);
	}
}


void Player::drawStats() {
	this->drawHealthBar(this->getInventory()->getStartingX(), this->getInventory()->getStartingY() - 30);

	this->drawThirstBar(this->getInventory()->getStartingX() + 35 * ((this->getInventory()->getWidth()) / 100), this->getInventory()->getStartingY() - 30);

	this->drawHungerBar(this->getInventory()->getStartingX() + 7 * ((this->getInventory()->getWidth()) / 10), this->getInventory()->getStartingY() - 30);
}

bool Player::getWithinDarkness()
{
	return this->withinDarkness;
}

void Player::setWithinDarkness(bool newDarkness)
{
	this->withinDarkness = newDarkness;
}

Player::~Player() {
	SDL_DestroyTexture(hungerBar);
	SDL_DestroyTexture(hungerBarContainer);

	SDL_DestroyTexture(healthBar);
	SDL_DestroyTexture(healthBarContainer);

	SDL_DestroyTexture(thirstBar);
	SDL_DestroyTexture(thirstBarContainer);

	PlayState::Instance()->getMainEntityContainer()->getDrawableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getCollidableContainer()->remove(this);
	PlayState::Instance()->getMainEntityContainer()->getMovableContainer()->remove(this);

	delete this->inventory;
	delete this->crafting;
	delete this->statusTracker;

	this->inventory = nullptr;
	this->crafting = nullptr;
	this->statusTracker = nullptr;
}
