#pragma once
#include "igamestate.h"
#include "header_loader.h"
#include "Player.h"
#include "Camera.h"
#include "MainEntityContainer.h"
#include "MapLoader.h"
#include "GameTimer.h"
#include "DayTimeTimer.h"

class PlayState : public IGameState
{
private:
	static PlayState m_PlayState;

	GameStateManager* gsm;

	MapLoader* mapLoader;
	MainEntityContainer* mec;

	SDL_Surface* bg;
	int alpha;

	int counter;
	Camera* camera;

	Player* p;
	std::vector<DrawableEntity*> temp;

	GameTimer* gameTimer;
	DayTimeTimer* dayTimer;

public:

	void init(GameStateManager *gsm);
	void cleanup();

	void pause();
	void resume();

	void handleEvents(SDL_Event mainEvent) ;

	void update(double dt);
	void updateGameTimers();
	long getGameTimer();

	void draw();

	static PlayState* Instance() {
		return &m_PlayState;
	};

	PlayState(void);
	~PlayState(void);
};
