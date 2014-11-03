#include "Player.h"
#include "header_loader.h"
#include <iostream>
#include "Inventory.h"


Player::Player(int id, double moveSpeed, double x, double y, int chunkSize, Camera* camera, GameStateManager* gsm, MainEntityContainer* mec)
	: Entity(id,x,y,chunkSize), DrawableEntity(id,x,y,chunkSize, nullptr), CollidableEntity(id,x,y,chunkSize), IMovable(moveSpeed)
{
	this->mec = mec;
	this->camera = camera;
	this->gsm = gsm;

	//Entity -> dimension values
	this->setWidth(64);
	this->setHeight(64);

	this->playerTimer = new PlayerUpdateTimer();
	this->health = 100, this->hunger = 100, this->thirst = 100;

	//CollidableEnity - collision values
	this->setCollisionHeight(this->getHeight() - 15);
	this->setCollisionWidth(this->getWidth()/4);
	this->setCollisionX((this->getWidth() - this->getCollisionWidth()) / 2);
	this->setCollisionY(0);

	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 3;

	this->setTempX(this->getX());
	this->setTempY(this->getY());

	this->stopSpeed = 0.8;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	this->moveClick = false;
	this->interaction = false;

	this->firstImgID = gsm->getImageLoader()->loadTileset("Player_Dagger.png", 64, 64);
	this->playerAnimationWalkUpRow = 8, this->playerAnimationWalkLeftRow = 9;
	this->playerAnimationWalkDownRow = 10, this->playerAnimationWalkRightRow = 11;
	this->currentPlayerAnimationRow = this->playerAnimationWalkDownRow;
	this->playerAnimationIdleColumn = 0; this->playerAnimationWalkStartColumn = 1, this->playerAnimationWalkEndColumn = 8;
	this->playerAnimationActionStartColumn = 1; this->playerAnimationActionEndColumn = 5;
	this->frameAmountX = 13, this->frameAmountY = 21, this->CurrentFrame = 0;
	this->animationSpeed = 10;//, this->animationDelay = 1;

	//Set camera
	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));

	this->StopAnimation();

	//Add to containers
	mec->getDrawableContainer()->add(this);
	//TODO : collision container

	this->inventory = new Inventory();
}

Inventory* Player::getInventory() {
	return this->inventory;
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

bool Player::checkCollision(CollidableContainer* container) {
	//TODO: werkend maken met nieuwe collidablecontainer shit
	double currentX = this->getX();
	double currentY = this->getY();
	this->setX(this->tempX);
	this->setY(this->tempY);

	//Calculate begin and end chunks for the player collision (+1 and -1 to make it a little bigger thent he current chunk)
	int beginChunkX = this->getChunkX() - 1;
	int endChunkX = this->getChunkX() + 1;
	int beginChunkY = this->getChunkY() - 1;
	int endChunkY = this->getChunkY() + 1;

	//Loop through all chunks
	for(int i = beginChunkY; i <= endChunkY; i++)
	{
		for(int j = beginChunkX; j <= endChunkX; j++)
		{
			std::vector<CollidableEntity*>* vec = this->mec->getCollidableContainer()->getChunk(i, j);
			if(vec != nullptr)
			{
				for(CollidableEntity* e : *vec)
				{
					if (this->intersects(e)) {
						this->setX(currentX);
						this->setY(currentY);
						this->StopAnimation();
						return true;
					}
				}
			}
		}
	}

	return false;
}

void Player::update(double dt) {
	this->updatePlayerStatuses();
	this->move(dt);

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
void Player::updatePlayerStatuses()
{
	this->playerTimer->updateGameTime(this->gsm->lastUpdateLength);

	if ( playerTimer->updateHungerTime() )
	{
		if (this->getHunger() > 0)
			this->setHunger(-1);
		else 
			this->setHealth(-1);
	}

	if ( playerTimer->updateThirstTime() )
	{
		if (this->getThirst() > 0)
			this->setThurst(-1);
		else
			this->setHealth(-2);
	}
}

void Player::setHealth(int value)
{
	if ( (this->health + value)  > 100)
		this->health = 100;
	else
		this->health += value;
}

void Player::setHunger(int value)
{
	if ( (this->hunger + value)  > 100)
		this->hunger = 100;
	else if ( (this->hunger - value)  < 0 )
		this->hunger = 0;
	else
		this->hunger += value;
}

void Player::setThurst(int value)
{
	if ( (this->thirst + value)  > 100)
		this->thirst = 100;
	else if ( (this->thirst - value)  < 0 )
		this->thirst = 0;
	else
		this->thirst += value;
}

int Player::getHealth()
{
	return this->health;
}

int Player::getHunger()
{
	return this->hunger;
}

int Player::getThirst()
{
	return this->thirst;
}
#pragma endregion PlayerStatusUpdates

void Player::move(double dt) {

	if(moveClick) {
		clickMove();
	}

	if (movingLeft) {
		dx -= moveSpeed *dt;
		if (dx < -maxSpeed *dt) {
			dx = -maxSpeed *dt;
		}
	} else if (movingRight) {
		dx += moveSpeed *dt;
		if (dx > maxSpeed *dt) {
			dx = maxSpeed *dt;
		}
	} else {
		if (dx > 0) {
			dx -= stopSpeed *dt;
			if (dx < 0) {
				dx = 0;
			}
		} else if (dx < 0) {
			dx += stopSpeed *dt;
			if (dx > 0) {
				dx = 0;
			}
		}
	}

	if (movingUp) {
		dy -= moveSpeed *dt;
		if (dy < -maxSpeed *dt) {
			dy = -maxSpeed *dt;
		}
	} else if (movingDown) {
		dy += moveSpeed *dt;
		if (dy > maxSpeed *dt) {
			dy = maxSpeed *dt;
		}
	} else {
		if (dy > 0) {
			dy -= stopSpeed *dt;
			if (dy < 0) {
				dy = 0;
			}
		} else if (dy < 0) {
			dy += stopSpeed *dt;
			if (dy > 0) {
				dy = 0;
			}
		}
	}

	if (dx == 0 && dy == 0) {
		return;
	}

	//if (dx != 0 && dy != 0) {

	//dx = dx / 2;
	//dy = dy / 2;

	//dx = dx / (moveSpeed / 2);
	//dy = dy / (moveSpeed / 2);
	//}

	//Move player
	this->setTempX(getX() + dx);
	this->setTempY(getY() + dy);



	/*this->setX(getX() + dx);
	this->setY(getY() + dy);*/

	//Temp:
	//this->mapX = this->getX();
	//this->mapY = this->getY();

	//Move camera

	// set animation row
	if (this->movingLeft)
		this->currentPlayerAnimationRow = this->playerAnimationWalkLeftRow;
	else if (this->movingRight)
		this->currentPlayerAnimationRow = this->playerAnimationWalkRightRow;
	else if (this->movingUp)
		this->currentPlayerAnimationRow = this->playerAnimationWalkUpRow;
	else if (this->movingDown)
		this->currentPlayerAnimationRow = this->playerAnimationWalkDownRow;

	PlayAnimation(this->playerAnimationWalkStartColumn, this->playerAnimationWalkEndColumn, this->currentPlayerAnimationRow, dt);

}

void::Player::interact()
{
	//Calculate begin and end chunks for the player collision (+1 and -1 to make it a little bigger thent he current chunk)
	int beginChunkX = this->getChunkX() - 1;
	int endChunkX = this->getChunkX() + 1;
	int beginChunkY = this->getChunkY() - 1;
	int endChunkY = this->getChunkY() + 1;

	int playerOffsetX = this->getX() + (this->getWidth() / 2);
	int playerOffsetY = this->getY() + (this->getHeight() / 2);

	double diff = 1000;
	InteractableEntity* closestEntity = nullptr;

	//Loop through all chunks
	for(int i = beginChunkY; i <= endChunkY; i++)
	{
		for(int j = beginChunkX; j <= endChunkX; j++)
		{
			std::vector<InteractableEntity*>* vec = this->mec->getInteractableContainer()->getChunk(i, j);
			if(vec != nullptr)
			{


				for(InteractableEntity* e : *vec)
				{
					
					if((playerOffsetX >= e->getInteractAreaStartX() && playerOffsetX <= e->getInteractAreaEndX()) && 
						(playerOffsetY >= e->getInteractAreaStartY() && playerOffsetY <= e->getInteractAreaEndY()))
					{
						double centerX = (e->getInteractAreaStartX() + e->getInteractAreaEndX()) / 2;
						double centerY = (e->getInteractAreaStartY() + e->getInteractAreaEndY()) / 2;

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
							//std::cout << "New Closest Entity" << std::endl;
						}



						//e->interact(this);
						//TODO : let op, nu pakt die het eerste object dat die tegen komt om mee te interacten, dit is niet persee de dichtsbijzijnde
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
	//this->setX(getX() + dx);
	//this->setY(getY() + dy);

	this->setX(this->tempX);
	this->setY(this->tempY);

	//Chance chunks if needed
	if(floor(this->getY() / this->getChunkSize()) != this->getChunkY() || floor(this->getX() / this->getChunkSize()) != this->getChunkX()) 
	{  
		//TODO : Put the player in another chunk in ALLL CONTAINERSSSS
		this->mec->getDrawableContainer()->remove(this);
		this->setChunks(); 
		this->mec->getDrawableContainer()->add(this);
	} 

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

void Player::PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt) {
	double animationDelay = (maxSpeed / 100)  * 40;
	animationSpeed -= animationDelay;
	if ( animationSpeed < animationDelay) {
		this->currentPlayerAnimationRow = Row;
		if (EndFrame <= CurrentFrame)
			CurrentFrame = BeginFrame;
		else
			CurrentFrame++;

		this->setDrawImage(gsm->getImageLoader()->getMapImage(firstImgID + (currentPlayerAnimationRow * frameAmountX) + CurrentFrame));
		animationSpeed = maxSpeed * 3;
	}
}

void Player::StopAnimation() {
	this->setDrawImage(gsm->getImageLoader()->getMapImage(firstImgID + (currentPlayerAnimationRow * frameAmountX) + playerAnimationIdleColumn));
}

Player::~Player(void) {
	delete this->inventory;
}