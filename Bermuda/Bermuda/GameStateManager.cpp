#include "GameStateManager.h"
#include "IGameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include <iostream>
#include <Windows.h>
#include <SDL_ttf.h>

GameStateManager GameStateManager::m_Gsm;
GameStateManager::GameStateManager() {
}

void GameStateManager::init(const char* title, int width, int height, int bpp, bool fullscreen) {

	speedMultiplier = 1;

	sdlInitializer = new SDLInitializer();
	sdlInitializer->init(title, width, height, bpp, fullscreen);

	GameStateManager::Instance()->changeGameState(MenuState::Instance());

	actionContainer = new ActionContainer();

	m_running = true;
	showFps = false;
	showHelp = false;

	GameStateManager::Instance()->setFps(0);
	this->updateLength = 0;
}

void GameStateManager::setUpdateLength(float updateLength) {
	this->updateLength = updateLength;
}

bool GameStateManager::helpEnabled() {
	return this->showHelp;
}

void GameStateManager::toggleHelpEnabled() {
	this->showHelp = !this->showHelp;
}

float GameStateManager::getUpdateLength() {
	cout.precision(10);
	std::cout << "UL: " << this->updateLength << "  SM: " << this->speedMultiplier << " TOTAL: " << this->updateLength * speedMultiplier << std::endl;
	return this->updateLength * speedMultiplier;
}

void GameStateManager::setSpeedMultiplier(double multiplier) {
	if (multiplier > 10) {
		this->speedMultiplier = 10;
	} else if (multiplier < 0.1) {
		this->speedMultiplier = 0.1;
	} else {
		this->speedMultiplier = multiplier;
	}
}

double GameStateManager::getSpeedMultiplier() {
	return this->speedMultiplier;
}

void GameStateManager::setFps(int fps) {
	GameStateManager::Instance()->fps = fps;
}

int GameStateManager::getFps() {
	return GameStateManager::Instance()->fps;
}

void GameStateManager::changeGameState(IGameState* gameState) {
	while (!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}

	states.push_back(gameState);
	states.back()->init(GameStateManager::Instance());
}

void GameStateManager::pushGameState(IGameState* gameState) {
	if (!states.empty()) {
		states.back()->pause();
	}

	states.push_back(gameState);
	states.back()->init(GameStateManager::Instance());
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
		case SDL_QUIT:
			this->m_running = false;
			break;
		case SDL_KEYDOWN:
			switch(mainEvent.key.keysym.sym) 
			{
			case SDLK_TAB:
				GameStateManager::Instance()->showFps = !GameStateManager::Instance()->showFps;
				break;
			case SDLK_PAGEUP:
				if (this->getSpeedMultiplier() > 0.9) {
					this->setSpeedMultiplier(this->getSpeedMultiplier() + 1);
				} else {
					this->setSpeedMultiplier(this->getSpeedMultiplier() + 0.1);
				}
				std::cout << "SPEED UP: " << speedMultiplier << std::endl;
				break;
			case SDLK_PAGEDOWN:
				if (this->getSpeedMultiplier() <= 1) {
					this->setSpeedMultiplier(this->getSpeedMultiplier() - 0.1);
				} else {
					this->setSpeedMultiplier(this->getSpeedMultiplier() - 1);
				}
				std::cout << "SPEED DOWN: " << speedMultiplier << std::endl;
				break;
			case SDLK_HOME:
				speedMultiplier = 1;
				break;
			default: 
				states.back()->handleEvents(mainEvent);
				break;
			}
			break;
		case SDL_KEYUP:
			//Switch pas nodig als er meerdere cases zijn... nu een switch gebruiken met alleen default is overbodig
			/*switch(mainEvent.key.keysym.sym) {
			default:
				states.back()->handleEvents(mainEvent);
				break;
			}*/
			states.back()->handleEvents(mainEvent);
			break;
		default:
			states.back()->handleEvents(mainEvent);
			break;
		}
	}
}

void GameStateManager::flushEvents()
{
	SDL_Event mainEvent;
	while (SDL_PollEvent(&mainEvent))
	{
		SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
		SDL_FlushEvent(SDL_MOUSEMOTION);
		SDL_FlushEvent(SDL_MOUSEWHEEL);
		SDL_FlushEvent(SDL_KEYDOWN);
		SDL_FlushEvent(SDL_KEYUP);
		SDL_FlushEvent(SDL_QUIT);
	}
}

void GameStateManager::update(double deltaTime) {
	states.back()->update(deltaTime * speedMultiplier);
}

void GameStateManager::draw() {
	//Clear Screen
	GameStateManager::Instance()->sdlInitializer->clearScreen();

	//OPTION ONE: Draw all GameStates
	for (size_t  i = 0; i < states.size(); i++) 
	{
		states.at(i)->draw();
	}

	//OPTION TWO: Draw only top state (does not work when pause state is on ... background will be black)
	//states.back()->draw();

	//Draw FPS
	if (GameStateManager::Instance()->showFps == true) {
		GameStateManager::Instance()->sdlInitializer->drawText(std::string("FPS: " + to_string(GameStateManager::Instance()->getFps())), 5, 5, 50, 24);
	}

	//Draw entire screen
	GameStateManager::Instance()->sdlInitializer->drawScreen();
}

ActionContainer* GameStateManager::getActionContainer() {
	return actionContainer;
}

void GameStateManager::quitGame()
{
	this->m_running = false;
}

bool GameStateManager::running() {
	return m_running;
}

void GameStateManager::quit() {
	m_running = false;
	SDL_Quit();
}

void GameStateManager::cleanup() 
{
	//While there are states on the stack, clean them up
	while (!states.empty()) {
		//Peek at top state and clean that state
		states.back()->cleanup();

		//Remove top state
		states.pop_back();
	}

	delete this->sdlInitializer;
	delete this->actionContainer;
}

GameStateManager::~GameStateManager() 
{
}
