#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameStateManager.h"

class PauzeBaseButton
{
private:
	//Variables
	bool active;

	//Methodes
	virtual void action() = 0;

protected:
	//Variables
	SDL_Texture* ButtonTexture;
	SDL_Texture* HoverButtonTexture;
	SDL_Rect ButtonRect;

public:
	//methodes
	void createButton(std::string);
	void placeAbove(PauzeBaseButton* button);
	void placeUnder(PauzeBaseButton* button);
	int getX();
	int getY();
	int getHeight();
	int getWidth();

	void draw();
	void hover(int, int);
	bool clicked(int, int);

	//constructors initialize, cleanup and delete
	PauzeBaseButton();
	virtual void init() = 0;
	void cleanup();
	virtual ~PauzeBaseButton();
};

