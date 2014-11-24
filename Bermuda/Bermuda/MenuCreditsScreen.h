#pragma once
#include "BaseScreen.h"
#include "GameStateManager.h"

class MenuCreditsScreen :
	public BaseScreen
{
private:
	//variables
	SDL_Texture* bermudaTextTexture;
	SDL_Rect bermudaTextRect;
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;
	std::vector<std::string> names;
	std::vector<SDL_Texture*> nameTextures;
	std::vector<SDL_Rect> nameRectangles;

	//methodes
	void init();
	void cleanup();
	void setBackground();

	void setNames();
	void createNameTextures();
	void align();

public:
	//methodes
	void handleEvents(SDL_Event);
	void draw();

	//constructors destructors
	MenuCreditsScreen();
	virtual ~MenuCreditsScreen();
};

