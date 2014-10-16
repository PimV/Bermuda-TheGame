#include "GameStateManager.h"
#include "IGameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include <iostream>
#include <Windows.h>
#include <SDL_ttf.h>


GameStateManager::GameStateManager(void) {
	init("Bermuda", ScreenWidth, ScreenHeight, 0, fullScreen);
}

void GameStateManager::init(const char* title, int width, int height, int bpp, bool fullscreen) {
	sdlInitializer = new SDLInitializer();
	sdlInitializer->init(title, width, height, bpp, fullscreen);
	imgLoader = new ImageLoader(sdlInitializer->getRenderer());
	soundLoader = new SoundLoader();

	this->changeGameState(MenuState::Instance());

	actionContainer = new ActionContainer();

	m_running = true;
	showFps = false;
	this->setFps(0);
}

void GameStateManager::setFps(int fps) {
	this->fps = fps;
}

int GameStateManager::getFps() {
	return this->fps;
}

void GameStateManager::cleanup() {
	//While there are states on the stack, clean them up
	while (!states.empty()) {
		//Peek at top state and clean that state
		states.back()->cleanup();

		//Remove top state
		states.pop_back();
	}
}

void GameStateManager::changeGameState(IGameState* gameState) {
	if (!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}

	states.push_back(gameState);
	states.back()->init(this);
}

void GameStateManager::pushGameState(IGameState* gameState) {
	if (!states.empty()) {
		states.back()->pause();
	}

	states.push_back(gameState);
	states.back()->init(this);
}

void GameStateManager::popState() {
	if (!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}

	if (!states.empty()) {
		states.back()->resume();
	}
}

void GameStateManager::handleEvents() {
	SDL_Event mainEvent;

	while(SDL_PollEvent(&mainEvent)) 
	{
		switch(mainEvent.type) 
		{
		case SDL_KEYDOWN:
			switch(mainEvent.key.keysym.sym) 
			{
			case SDLK_TAB:
				if (this->showFps == false) {
					this->showFps = true;
				}
				break;
			default: 
				states.back()->handleEvents(mainEvent);
				break;
			}
			break;
		case SDL_KEYUP:
			switch(mainEvent.key.keysym.sym) {
			case SDLK_TAB:
				if (this->showFps == true) {
					this->showFps = false;
				}
				break;
			default:
				states.back()->handleEvents(mainEvent);
				break;
			}
			break;
		default:
			states.back()->handleEvents(mainEvent);
			break;
		}
	}



}

void GameStateManager::update(double deltaTime) {
	states.back()->update(deltaTime);
}

void GameStateManager::draw() {
	//Clear Screen
	this->sdlInitializer->clearScreen();

	//Draw GameState
	for (size_t  i = 0; i < states.size(); i++) {
		states.at(i)->draw();
	}

	//Draw FPS
	if (this->showFps == true) {
		this->sdlInitializer->drawText(std::string("FPS: " + to_string(this->getFps())), 5, 5, 50, 24);
	}

	//Draw entire screen
	this->sdlInitializer->drawScreen();
}

ActionContainer* GameStateManager::getActionContainer() {
	return actionContainer;
}

bool GameStateManager::running() {
	return m_running;
}

void GameStateManager::quit() {
	m_running = false;
	SDL_Quit();
}

ImageLoader* GameStateManager::getImageLoader()
{
	return imgLoader;
}

SoundLoader* GameStateManager::getSoundLoader()
{
	return soundLoader;
}

GameStateManager::~GameStateManager(void) {
	delete imgLoader;
	delete sdlInitializer;

	delete actionContainer;
}



