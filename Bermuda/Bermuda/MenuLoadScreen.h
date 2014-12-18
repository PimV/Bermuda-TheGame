#pragma once
#include "basescreen.h"
#include "GameStateManager.h"
#include "BaseButton.h"
#include <map>

class MenuLoadScreen :
	public BaseScreen
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;
	std::vector<BaseButton*> buttons;
	std::map<std::string, int> savedGames;

	void init();
	void readSavedGames();
	void cleanup();
	void setBackground();

public:
	void resetButtons();
	void handleEvents(SDL_Event);
	void draw();

	MenuLoadScreen();
	virtual ~MenuLoadScreen();
};

