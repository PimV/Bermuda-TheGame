#pragma once
#include "igamestate.h"
#include "header_loader.h"
#include "Player.h"
#include "Camera.h"
#include "MainEntityContainer.h"
#include "MapLoader.h"
#include "GameTimer.h"
#include "NightLayer.h"

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
	bool mapLoaded;
	Camera* camera;

	Player* p;
	std::vector<DrawableEntity*> temp;

	int timesUpdate;
	bool ready;

	bool showCol, showInter, showSpawnArea, showDayLight;

	NightLayer* nightLayer;

	static bool PlayState::drawableSortFunction(DrawableEntity* one, DrawableEntity* two);

public:
	PlayState();
	Player* getPlayer();
	MainEntityContainer* getMainEntityContainer();

	void init(GameStateManager *gsm);
	void cleanup();

	void pause();
	void resume();

	void handleEvents(SDL_Event mainEvent);

	void update(double dt);

	void updateVisibleEntities(double dt);
	void updateMediumAreaEntities(double dt);

	void updateGameTimers(double dt);	

	void draw();

	Camera* getCamera();

	static PlayState* Instance() {
		return &m_PlayState;
	};

	virtual ~PlayState();
};
