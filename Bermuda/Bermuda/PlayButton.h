#pragma once
#include "BaseButton.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "PlayState.h"

class PlayButton :
	public BaseButton
{
public:
	//Methodes
	void init();
	void loadHoverPicture(GameStateManager *gsm);
	void loadNormalPicture(GameStateManager *gsm);
	void action(GameStateManager *gsm);

	//Constructor and destructor
	PlayButton(GameStateManager *gsm);
	virtual ~PlayButton();
};

