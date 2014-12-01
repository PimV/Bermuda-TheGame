#pragma once
#include "igamestate.h"
#include "header_loader.h"
#include "Player.h"
#include "Camera.h"
#include "MainEntityContainer.h"
#include "MapLoader.h"
#include "GameTimer.h"

//temp
class Axe;

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

	//std::vector<Entity*> lightEntities;
	SDL_Surface* blackSurface;
	SDL_Surface* lightSourceImage;
	void calculateAlpha(SDL_Texture* texture);
	void drawDarkness();
	int alphaLevel;

	static bool PlayState::drawableSortFunction(DrawableEntity* one, DrawableEntity* two);

public:
	Player* getPlayer();
	MainEntityContainer* getMainEntityContainer();

	void init(GameStateManager *gsm);
	void cleanup();

	void pause();
	void resume();

	void handleEvents(SDL_Event mainEvent);

	void update(double dt);
	void updateGameTimers(double dt);


	void draw();

	Camera* getCamera();

	static PlayState* Instance() {
		return &m_PlayState;
	};

	PlayState(void);
	~PlayState(void);
};
