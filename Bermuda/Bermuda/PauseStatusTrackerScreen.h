#pragma once
#include <SDL.h>
#include <vector>

class PauseStatusTrackerScreen
{
private:
	//variables
	std::vector<SDL_Texture*> nameTextures;
	std::vector<SDL_Rect> nameRectangles;
	std::vector<SDL_Surface*> nameSurfaces;

	std::vector<SDL_Texture*> countTextures;
	std::vector<SDL_Rect> countRectangles;
	std::vector<SDL_Surface*> countSurfaces;

	//Methodes
	void init();
	void cleanup();

public:
	//Methodes
	void handleEvents(SDL_Event);
	void draw();

	//Constructor destructors
	PauseStatusTrackerScreen();
	virtual ~PauseStatusTrackerScreen();
};

