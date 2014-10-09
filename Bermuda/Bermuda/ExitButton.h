#pragma once
#include "BaseButton.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class ExitButton :
	public BaseButton
{
public:
	//methodes
	void init();
	void loadHoverPicture(GameStateManager *gsm);
	void loadNormalPicture(GameStateManager *gsm);
	void action(GameStateManager *gsm);

	//Constructors and destructors
	ExitButton(GameStateManager *gsm);
	virtual ~ExitButton();
};

