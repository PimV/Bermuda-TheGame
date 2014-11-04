#pragma once
#include "BasePauzeButton.h"

class PauseMainScreen
{
private:
	//variables
	std::vector<BasePauzeButton*> buttons;
	
	//methodes
	void init();
	void cleanup();

public:
	//methodes
	void handleEvents(SDL_Event);
	void draw();

	//constructors destructors
	PauseMainScreen();
	virtual ~PauseMainScreen();
};

