#pragma once
#include <SDL.h>
#include "header_loader.h"
#include <string>
#include "GameStateManager.h"

class MenuHelpScreen;

class BaseButton
{
public:
	//variables
	bool active;
	bool hoverAction;
	SDL_Texture* buttonTexture;
	SDL_Texture* buttonHoverTexture;
	SDL_Rect buttonRect;
	MenuHelpScreen* helpScr;

public:
	//methodes
	void createButton(std::string buttonText, int fontSize, int initialColor);
	void setNewButtonText(std::string text, int fontSize, int initialColor);
	void reset();
	void placeLeftAboveButton(BaseButton* button);
	void placeLeftUnderButton(BaseButton* button);
	void placeLeftUnder(int xOffset, int yOffset);
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
	void setHelpScr(MenuHelpScreen*);
	void setHoverAction(bool falseOrTrue);

	//buttonActions
	void setCreditsScreenAction();
	void setLoadScreenAction();
	void exitAction();
	void menuSetHelpScreenAction();
	void playAction();
	void pauseSetAchievementScreenAction();
	void backToPauseMainScreenAction();
	void backToMenuAction();
	void resumeGameAction();
	void menuMainScreenAction();
	void helpMovementScreenAction();
	void helpCutTreeScreenAction();
	void helpCutCactusScreenAction();
	void helpFishScreenAction();
	void helpPickAppleScreenAction();
	void helpPickCarrotScreenAction();
	void helpMineGoldScreenAction();
	void helpMineIceScreenAction();
	void helpMineRockScreenAction();
	void helpFoodAndWaterScreenAction();
	void helptimeScreenAction();

	void draw();
	void hover(int, int);
	virtual bool clicked(int, int);
	void (BaseButton::*action) ();

	BaseButton();
	void cleanup();
	virtual ~BaseButton();
};

