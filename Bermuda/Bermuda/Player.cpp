#include "Player.h"
#include <iostream>


Player::Player(int id, double moveSpeed, Camera* camera)
	: Entity(id), IMovable(moveSpeed)
{
	this->camera = camera;
	
	//TODO: Change setx and sety to spawnlocation
	this->setX(350);
	this->setY(350);
	this->dx = 0;
	this->dy = 0;
	this->maxSpeed = 5;

	this->stopSpeed = 0.8;
	//this->moveSpeed = id;
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	this->moveClick = false;

	//this->path = "F.png";
	this->path = "Player_Dagger.png";
	this->frameAmountX = 0, this->frameAmountY = 0, this->CurrentFrame = 0;
	crop.x = 0;
	crop.y = 0;
	crop.w = 0;
	crop.h = 0;

	// amount of sprites in the sheet
	this->SetupAnimation(13, 21);
	
	//Set camera
	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));
}

void Player::resetMovement()
{
	if (moveClick) {
	this->movingLeft = false;
	this->movingRight = false;
	this->movingDown = false;
	this->movingUp = false;
	this->moveClick = false;
	}
}

void Player::move(double dt) {
	
	if(moveClick)
	{
		clickMove();		
	}

	if (movingLeft) {
		dx -= moveSpeed *dt;
		if (dx < -maxSpeed *dt) {
			dx = -maxSpeed;
		}
	} else if (movingRight) {
		dx += moveSpeed *dt;
		if (dx > maxSpeed*dt) {
			dx = maxSpeed;
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
		if (dy < -maxSpeed*dt) {
			dy = -maxSpeed;
		}
	} else if (movingDown) {
		dy += moveSpeed *dt;
		if (dy > maxSpeed*dt) {
			dy = maxSpeed;
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

	if (dx != 0 && dy != 0) {
		dx = dx / 2;
		dy = dy / 2;
	}

	//Move player
	this->setX(getX() + dx *dt);
	this->setY(getY() + dy *dt);

	//Move camera
	this->camera->setX((this->getX() + this->getWidth() / 2) - (this->camera->getWidth() / 2));
	this->camera->setY((this->getY() + this->getHeight() / 2) - (this->camera->getHeight() / 2));

	
	if (this->movingLeft) {
		path = "L.png";
	}
	else if (this->movingRight) {
		path = "R.png";
	}
	else if (this->movingUp) {
		path = "B.png";
	}
	else if (this->movingDown) {
		path = "F.png";
	}
}

void Player::clickMove(){
	std::cout << destX << " - " << destY << std::endl;
	std::cout << getX() << " get-get " << getY() << std::endl;

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

void Player::LoadSpriteSheet(std::string path, SDL_Renderer *renderer)
{
	texture = IMG_LoadTexture(renderer, path.c_str());
	int textureWidth, textureHeight;
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

	this->setWidth(textureWidth);
	this->setHeight(textureHeight);
}

void Player::SetupAnimation(int amountFrameX, int amountFrameY)
{
	frameAmountX = amountFrameX, frameAmountY = amountFrameY;
	
	// The rest of is calculated in PlayAnimation()
	crop.w = this->getWidth()/frameAmountX;
	crop.h = this->getHeight()/frameAmountY;
}

void Player::PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed)
{
	if (EndFrame <= CurrentFrame)
		CurrentFrame = BeginFrame;
	else
		CurrentFrame++;

	crop.x = CurrentFrame * (this->getWidth()/frameAmountX);
	crop.y = Row * (this->getHeight()/frameAmountY);
	// The rest is set in SetupAnimation(), for is doesn't change
}

void Player::StopAnimation(int Row)
{
	this->PlayAnimation(0, 0, Row, 0);
}

void Player::draw(SDLInitializer* sdlInitializer) {
	//std::string path = "front.bmp";

	SDL_Texture* texture = IMG_LoadTexture(sdlInitializer->getRenderer(), path);

	if (texture == NULL) {
		std::cout << "NO PLAYER IMAGE" << std::endl;
	}

	//SDL_Surface*  img = SDL_LoadBMP(path);
	//SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlInitializer->getRenderer(), img);

	SDL_Rect rect;
	rect.w = this->getWidth();
	rect.h = this->getHeight();
	rect.x = getX() - this->camera->getX();
	rect.y = getY() - this->camera->getY();

	//Add texture to renderer

	sdlInitializer->drawTexture(texture, &rect);

	//	sdlInitializer->drawScreen();

	//Clean created textures/surfaces
	SDL_DestroyTexture(texture);  
	//SDL_FreeSurface(img); 
}

Player::~Player(void)
{
	SDL_DestroyTexture(texture);
}