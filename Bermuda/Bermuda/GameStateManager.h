#pragma once
#include "header_loader.h"
#include "SDLInitializer.h"
#include "ActionContainer.h"
#include "ImageLoader.h"
#include "SoundLoader.h"
#include <vector>

class IGameState;

class GameStateManager
{
public:
	bool showFps;
	GameStateManager(void);

	void init(const char* title, int width, int height, int bpp, bool fullscreen);
	void cleanup();

	void setFps(int fps);
	int getFps();

	void changeGameState(IGameState* gameState);
	void pushGameState(IGameState* gameState);
	void popState();

	void updateGameTime(long time);

	void update(double delta);
	void handleEvents();
	void draw();

	void setUpdateLength(long updateLength);
	long getUpdateLength();

	ActionContainer* getActionContainer();

	bool running();
	bool helpEnabled();
	void toggleHelpEnabled();
	void quit();
	SDLInitializer* sdlInitializer;
	ImageLoader* getImageLoader();
	SoundLoader* getSoundLoader();

	double getSpeedMultiplier();
	void setSpeedMultiplier(double multiplier);


	static GameStateManager* Instance() {
		return &m_Gsm;
	};

	~GameStateManager(void);

private: 
	long updateLength;
	double speedMultiplier;
	int fps;
	bool showHelp;
	std::vector<IGameState*> states;
	IGameState* currentState;
	ImageLoader* imgLoader;
	SoundLoader* soundLoader;
	bool m_running;

	static GameStateManager m_Gsm;

	ActionContainer* actionContainer;
};
