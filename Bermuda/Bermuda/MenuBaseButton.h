#pragma once
#include <SDL.h>
#include "header_loader.h"
#include <string>
#include "GameStateManager.h"

class MenuBaseButton
{
public:
	//variables
	bool active;

protected:
	//variables
	SDL_Texture* buttonTexture;
	SDL_Texture* buttonHoverTexture;
	SDL_Rect buttonRect;

	//virtual methodes
	virtual void action() = 0;

public:
	
	//methodes
	void createButton(std::string buttonText, int fontSize);
	void placeAbove(MenuBaseButton* button);
	void placeUnder(MenuBaseButton* button);
	void placeMidUnder(int x, int y);
	int getHeight();
	int getWidth();
	void draw();
	void hover(int, int);
	bool clicked(int, int);

	MenuBaseButton();
	virtual void init() = 0;
	void cleanup();
	virtual ~MenuBaseButton();
};

