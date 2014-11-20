#pragma once
#include <SDL.h>
class BasePauseScreen
{
private:
	//Methodes
	virtual void init() = 0;
	virtual void cleanup() = 0;
	virtual void setBackground() = 0;

public:
	//Methodes
	virtual void handleEvents(SDL_Event) = 0;
	virtual void draw() = 0;

	BasePauseScreen();
	virtual ~BasePauseScreen();
};

