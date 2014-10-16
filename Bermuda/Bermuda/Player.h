#pragma once
#include "entity.h"
#include "IMovable.h"
#include "header_loader.h"
#include "Camera.h"
#include "DrawableEntity.h"
#include "CollidableEntity.h"
#include "GameStateManager.h"
#include "SDLInitializer.h"
#include "CollidableContainer.h"

class Player :
	public IMovable,
	public DrawableEntity,
	public CollidableEntity
{
public:
	Player(int id, double moveSpeed, Camera* camera, GameStateManager* gsm);
	//virtual void move(EnumDirection direction) = 0;
	virtual void move(double dt);
	//void clickMove();
	void clickMove();
	void setPosition();
	void resetMovement();
	void LoadSpriteSheet(std::string path, SDL_Renderer *renderer);
	void SetupAnimation(int amountFramesX, int amountFramesY);
	void PlayAnimation(int BeginFrame, int EndFrame, int Row, double dt);
	void StopAnimation();

	void draw(SDLInitializer* sdlInitializer);
	bool checkCollision(CollidableContainer* container);
	~Player(void);

	bool movingLeft;
	bool movingRight;
	bool movingUp;
	bool movingDown;
	bool moveClick;
	int destX;
	int destY;
private:
	const char* path;
	Camera* camera;

	SDL_Rect crop;
	SDL_Texture* texture;

	int currentPlayerAnimationRow, playerAnimationIdle;
	int playerAnimationWalkUp, playerAnimationWalkLeft, playerAnimationWalkDown, playerAnimationWalkRight;
	int playerAnimationWalkStart, playerAnimationWalkEnd;
	int frameAmountX, frameAmountY, CurrentFrame;
	double animationSpeed, animationDelay;

	double getDistence(int currentX, int currentY, int destX, int destY);
	//std::string* path;
};
