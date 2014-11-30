#pragma once
#include <SDL.h>
#include "header_loader.h"
#include <string>
#include "GameStateManager.h"

class BaseButton
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
	void createButton(std::string buttonText, int fontSize, int initialColor);
	void reset();
	void placeLeftAboveButton(BaseButton* button);
	void placeLeftUnderButton(BaseButton* button);
	void placeMidScreenAbove(BaseButton* button);
	void placeMidScreenUnder(BaseButton* button);
	void placeMid();
	void placeLeftMid();
	void placeMidUnder(int x, int y);
	int getX();
	int getY();
	int getHeight();
	int getWidth();

	void draw();
	void hover(int, int);
	bool clicked(int, int);

	BaseButton();
	virtual void init() = 0;
	void cleanup();
	virtual ~BaseButton();
};

