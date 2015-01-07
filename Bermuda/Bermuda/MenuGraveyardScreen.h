#pragma once
#include "BaseScreen.h"
#include <vector>
#include <list>
#include "BaseButton.h"
#include "Graveyard.h"

class MenuGraveyardScreen :
	public BaseScreen
{
private:
	//variables
	std::vector<SDL_Texture*> textures;
	std::vector<SDL_Rect> rectangles;
	int startTable;

	std::vector<BaseButton*> buttons;
	Graveyard* graveyard;

	//methodes
	void init();
	void cleanup();
	void setBackground();
	void createTable();


public:
	//methodes
	void resetButtons();
	void handleEvents(SDL_Event);
	void draw();

	//constructors destructors
	MenuGraveyardScreen();
	virtual ~MenuGraveyardScreen();
};