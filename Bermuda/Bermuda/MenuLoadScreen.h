#pragma once
#include "basescreen.h"
#include "GameStateManager.h"
#include "BaseButton.h"

class MenuLoadScreen :
	public BaseScreen
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;
	std::vector<BaseButton*> buttons;

	void init();
	void cleanup();
	void setBackground();

public:
	void resetButtons();
	void handleEvents(SDL_Event);
	void draw();

	MenuLoadScreen();
	virtual ~MenuLoadScreen();
};

