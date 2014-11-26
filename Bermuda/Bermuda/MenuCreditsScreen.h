#pragma once
#include "BaseScreen.h"
#include "GameStateManager.h"
#include "BaseButton.h"

class MenuCreditsScreen :
	public BaseScreen
{
private:
	//variables
	SDL_Texture* creditsTextTexture;
	SDL_Rect creditsTextRect;
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;
	std::vector<BaseButton*> buttons;
	std::vector<std::string> names;
	std::vector<SDL_Texture*> nameTextures;
	std::vector<SDL_Rect> nameRectangles;

	//methodes
	void init();
	void cleanup();
	void setBackground();

	void setNames();
	void createNameTextures();
	void createReturnButton();
	void align();

public:
	//methodes
	void handleEvents(SDL_Event);
	void draw();

	//constructors destructors
	MenuCreditsScreen();
	virtual ~MenuCreditsScreen();
};

