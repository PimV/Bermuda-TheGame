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
	ImageLoader* imgLoader;
	MapLoader* mapLoader;
	MainEntityContainer* mec;
	NightLayer* nightLayer;
	Camera* camera;
	Player* p;
	std::vector<DrawableEntity*> temp;

	int timesUpdate;
	bool gameOver;

	bool showCol, showInter, showSpawnArea, showDayLight;

	static bool PlayState::drawableSortFunction(DrawableEntity* one, DrawableEntity* two);

public:
	PlayState();
	ImageLoader* getImageLoader();
	Player* getPlayer();
	MainEntityContainer* getMainEntityContainer();
	Camera* getCamera();

	void init(GameStateManager *gsm);
	void cleanup();

	void pause();
	void resume();
	void setGameOver(bool gameOver);

	void handleEvents(SDL_Event mainEvent);

	void update(double dt);
	void updateVisibleEntities(double dt);
	void updateMediumAreaEntities(double dt);
	void updateGameTimers(double dt);	

	void updatePlayerDarkness();

	void draw();

	static PlayState* Instance() {
		return &m_PlayState;
	};

	virtual ~PlayState();
};
