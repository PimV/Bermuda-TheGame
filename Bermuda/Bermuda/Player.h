#pragma once
#include "entity.h"
#include "IMovable.h"
#include "header_loader.h"
#include "SDLInitializer.h"


class Player :
	public Entity,
	public IMovable
{
public:
	Player(int id, double moveSpeed);
	//virtual void move(EnumDirection direction) = 0;
	virtual void move(EnumDirection direction, double dt);// = 0;
	void draw(SDLInitializer* sdlInitializer);
	~Player(void);
	bool movingLeft;
	bool movingRight;
	bool movingUp;
	bool movingDown;
private:
	const char* path;
	//std::string* path;

};

