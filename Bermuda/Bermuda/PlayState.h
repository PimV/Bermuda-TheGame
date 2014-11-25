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
	/*temp timer*/
	SDL_Rect rectArrow;
	SDL_Rect rectFrame;
	SDL_Rect rectCircle;
	SDL_Texture* textCircle;
	SDL_Texture* textFrame;
	SDL_Texture* textArrow;

	int degrees;
	/*/temp timer*/

	static PlayState m_PlayState;

	GameStateManager* gsm;

	MapLoader* mapLoader;
	MainEntityContainer* mec;

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
