#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameStateManager.h"

class BasePauzeButton
{
private:
	//Variables
	bool active;

	//Methodes
	virtual void action(GameStateManager* gsm) = 0;

protected:
	//Variables
	SDL_Texture* ButtonTexture;
	SDL_Texture* HoverButtonTexture;
	SDL_Rect ButtonRect;

public:
	//methodes
	void placeAbove(BasePauzeButton* button);
	void placeUnder(BasePauzeButton* button);

	void draw(GameStateManager* gsm);
	void hover(int, int, GameStateManager *gsm);
	void clicked(int, int, GameStateManager *gsm);

	//constructors initialize, cleanup and delete
	BasePauzeButton();
	virtual void init(GameStateManager* gsm) = 0;
	void cleanup();
	virtual ~BasePauzeButton();
};

