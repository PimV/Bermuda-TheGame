#pragma once
#include "BaseButton.h"
#include "BaseScreen.h" 

class PauseMainScreen : public BaseScreen
{
private:
	//variables
	std::vector<BaseButton*> buttons;
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

