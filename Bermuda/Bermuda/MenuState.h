#pragma once
#include "ExitButton.h"
#include "PlayButton.h"
#include <SDL_image.h>
#include <SDL.h>
#include "igamestate.h"
#include "header_loader.h"
class MenuState :
	public IGameState
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;
	SDL_Texture* bermudaTextTexture;
	SDL_Rect bermudaTextRect;

	static const int totalButtons = 2;
	std::vector<BaseButton*> buttons;

	static MenuState m_MenuState;
	GameStateManager* gsm;

	SDL_Surface* bg;
	int alpha;

public:
	//TODO: put buttons in array

	void align();

	MenuState(void);
	void init(GameStateManager *gsm) ;
	void cleanup();

	void pause();
	void resume();

	void handleEvents(SDL_Event mainEvent) ;
	void update(double dt) ;
	void draw() ;

	static MenuState* Instance() {
		return &m_MenuState;
	}

	~MenuState(void);
};

