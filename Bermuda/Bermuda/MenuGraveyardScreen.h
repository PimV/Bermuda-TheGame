#pragma once
#include "BaseScreen.h"
#include <vector>
#include "BaseButton.h"

class MenuGraveyardScreen :
	public BaseScreen
{
private:
	//variables
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;
	SDL_Texture* graveyardTextTexture;
	SDL_Rect graveyardTextRect;
	std::vector<BaseButton*> buttons;

	//methodes
	void init();
	void cleanup();
	void setBackground();

public:
	//methodes
	void resetButtons();
	void handleEvents(SDL_Event);
	void draw();

	//constructors destructors
	MenuGraveyardScreen();
	virtual ~MenuGraveyardScreen();
};

