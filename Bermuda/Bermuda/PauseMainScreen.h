#pragma once
#include "BasePauzeButton.h"
#include "BasePauseScreen.h" 

class PauseMainScreen : public BasePauseScreen
{
private:
	//variables
	std::vector<BasePauzeButton*> buttons;
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;
	
	//methodes
	void init();
	void cleanup();
	void setBackground();

public:
	//methodes
	void handleEvents(SDL_Event);
	void draw();

	//constructors destructors
	PauseMainScreen();
	virtual ~PauseMainScreen();
};

