#pragma once
#include "igamestate.h"
#include "PlayState.h"
#include "header_loader.h"
#include "Player.h"
#include "Camera.h"
#include "MainEntityContainer.h"
#include "MapLoader.h"


class LoadingState : public IGameState
{
private:
	static LoadingState m_LoadingState;

	GameStateManager* gsm;
	
	SDL_Texture* text1;
	SDL_Texture* text2;
	SDL_Texture* textBackground;
	SDL_Texture* textAdvertisement;
	SDL_Rect rect1;
	SDL_Rect rect2;
	SDL_Rect rectBackground;
	SDL_Rect rectAdvertisement;
	
	int degrees;

	int percentage;

public:
	void init(GameStateManager *gsm);
	void cleanup();

	void pause();
	void resume();

	void handleEvents(SDL_Event mainEvent) ;
	void update(double dt);
	void draw();

	void setPercentage(int percentage);

	static LoadingState* Instance() {
		return &m_LoadingState;
	};

	LoadingState(void);
	~LoadingState(void);
};