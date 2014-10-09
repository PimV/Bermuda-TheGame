#pragma once
#include "entity.h"
#include "IMovable.h"
#include "header_loader.h"
#include "Camera.h"
#include "SDLInitializer.h"

class Player :
	public Entity,
	public IMovable
{
public:
	Player(int id, double moveSpeed, Camera* camera);
	//virtual void move(EnumDirection direction) = 0;
	virtual void move(double dt);
	void clickMove();
	void resetMovement();
	void LoadSpriteSheet(std::string path, SDL_Renderer *renderer);
	void SetupAnimation(int amountFramesX, int amountFramesY);
	void PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed);
	void StopAnimation(int Row);

	void draw(SDLInitializer* sdlInitializer);
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
	SDL_Texture *texture;
	int frameAmountX, frameAmountY, CurrentFrame;
	//std::string* path;
};
