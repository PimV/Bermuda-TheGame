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
	SDL_Texture* buttonTexture;
	SDL_Texture* buttonHoverTexture;
	SDL_Rect buttonRect;

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
	void placeExactAt(int x, int y);
	int getX();
	int getY();
	int getHeight();
	int getWidth();

	//buttonActions
	void setCreditsScreenAction();
	void exitAction();
	void menuSetHelpScreenAction();
	void playAction();
	void pauseSetAchievementScreenAction();
	void backToMenuAction();
	void resumeGameAction();
	void menuMainScreenAction();
	void helpMovementScreenAction();

	void draw();
	void hover(int, int);
	bool clicked(int, int);
	void (BaseButton::*action) ();

	BaseButton();
	void cleanup();
	virtual ~BaseButton();
};

