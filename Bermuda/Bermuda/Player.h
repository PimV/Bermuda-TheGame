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
	//std::string* path;

};

