#pragma once
#include <SDL.h>
class BaseScreen
{
private:
	//Methodes
	virtual void init() = 0;
	virtual void cleanup() = 0;
	virtual void setBackground() = 0;

public:
	//Methodes
	virtual void resetButtons() = 0;
	virtual void handleEvents(SDL_Event) = 0;
	virtual void draw() = 0;

	BaseScreen();
	virtual ~BaseScreen();
};

