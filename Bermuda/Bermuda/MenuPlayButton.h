#pragma once
#include "MenuBaseButton.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "PlayState.h"

class MenuPlayButton :
	public MenuBaseButton
{
public:
	//Methodes
	void init();
	void action();

	//Constructor and destructor
	MenuPlayButton();
	virtual ~MenuPlayButton();
};

