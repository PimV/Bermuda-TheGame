#include "GameStateManager.h"
#include "IGameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include <iostream>
#include <Windows.h>


GameStateManager::GameStateManager(void) {
	init("Bermuda", 1600, 900, 0, false);
}

void GameStateManager::init(const char* title, int width, int height, int bpp, bool fullscreen) {
	sdlInitializer = new SDLInitializer();
	sdlInitializer->init(title, width, height, bpp, fullscreen);
	imgLoader = new ImageLoader(sdlInitializer->getRenderer());

	this->changeGameState(MenuState::Instance());

	actionContainer = new ActionContainer();

	m_running = true;
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
	states.back()->handleEvents();
}

void GameStateManager::update(double deltaTime) {
	states.back()->update(deltaTime);
}

void GameStateManager::draw() {
	states.back()->draw();
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

GameStateManager::~GameStateManager(void) {
	delete imgLoader;
	delete sdlInitializer;

	delete actionContainer;
}



