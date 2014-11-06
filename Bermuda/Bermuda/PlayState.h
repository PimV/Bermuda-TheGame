#pragma once
#include "igamestate.h"
#include "header_loader.h"
#include "Player.h"
#include "Camera.h"
#include "MainEntityContainer.h"
#include "MapLoader.h"
#include "GameTimer.h"

class PlayState : public IGameState
{
private:
	static PlayState m_PlayState;

	GameStateManager* gsm;

	MapLoader* mapLoader;
	MainEntityContainer* mec;
		
	SDL_Texture* currentInteractText;
	SDL_Texture* currentInteractTextFront;
	SDL_Rect currentInteractRect;
	SDL_Rect currentInteractRectFront;

	SDL_Surface* bg;
	int alpha;

	int counter;
	bool mapLoaded;
	Camera* camera;

	Player* p;
	std::vector<DrawableEntity*> temp;

	bool ready;
	bool showCol, showInter, showSpawnArea; 

public:
	Player* getPlayer();
	MainEntityContainer* getMainEntityContainer();

	void init(GameStateManager *gsm);
	void cleanup();

	void pause();
	void resume();

	void handleEvents(SDL_Event mainEvent) ;

	void update(double dt);
	void updateGameTimers();
	long getGameTimer();

	void draw();

	Camera* getCamera();

	static PlayState* Instance() {
		return &m_PlayState;
	};

	PlayState(void);
	~PlayState(void);
};
