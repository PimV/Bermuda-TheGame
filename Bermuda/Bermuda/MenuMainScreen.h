#pragma once
#include "BaseScreen.h"
#include "GameStateManager.h"
#include "BaseButton.h"
#include <SDL_image.h>
#include <iostream>

class MenuMainScreen :
	public BaseScreen
{
private:
	//variables
	SDL_Texture* bermudaTextTexture;
	SDL_Rect bermudaTextRect;
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;

	//variables buttons
	std::vector<BaseButton*> buttons;

	//methodes
	void init();
	void cleanup();
	void setBackground();

public:
	//methodes
	void resetButtons();
	void handleEvents(SDL_Event);
	void draw();

	//constructors destructors
	MenuMainScreen();
	virtual ~MenuMainScreen();
};

