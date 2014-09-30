#include "GameStateManager.h"
#include "IGameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include <iostream>
#include <Windows.h>

GameStateManager::GameStateManager(void) {
	init("Bermuda", 640, 480, 0, false);
}

void GameStateManager::init(const char* title, int width, int height, int bpp, bool fullscreen) {
	sdlInitializer = new SDLInitializer();
	sdlInitializer->init(title, width, height, bpp, fullscreen);

	this->changeGameState(MenuState::Instance());
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
	states.back()->init();
}

void GameStateManager::pushGameState(IGameState* gameState) {
	if (!states.empty()) {
		states.back()->pause();
	}

	states.push_back(gameState);
	states.back()->init();
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
	states.back()->handleEvents(this);
}

void GameStateManager::update(double deltaTime) {
	states.back()->update(this, deltaTime);
}

void GameStateManager::draw() {
	states.back()->draw(this);
}

bool GameStateManager::running() {
	return m_running;
}

void GameStateManager::quit() {
	m_running = false;
	SDL_Quit();
}

GameStateManager::~GameStateManager(void) {
	delete sdlInitializer;
}



