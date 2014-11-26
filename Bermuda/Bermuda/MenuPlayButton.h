#pragma once
#include "BaseButton.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "PlayState.h"

class MenuPlayButton :
	public BaseButton
{
public:
	//Methodes
	void init();
	void action();

	//Constructor and destructor
	MenuPlayButton();
	virtual ~MenuPlayButton();
};

