#include "LoadingState.h"
#include "GameStateManager.h"
#include <iostream>

LoadingState LoadingState::m_LoadingState;

LoadingState::LoadingState(void)
{
}

void LoadingState::init(GameStateManager *gsm) {
	this->gsm = gsm;

	text1 = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "loading_bar_grey.png").c_str());
	text2 = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "loading_bar_green.png").c_str());
	textBackground = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "loading_background.png").c_str());

	rect1.x = ScreenWidth / 3;
	rect1.y = ScreenHeight / 2 - ScreenHeight / 40;
	rect1.h = ScreenHeight / 20;
	rect1.w = ScreenWidth / 3;

	rect2.x = ScreenWidth / 3;
	rect2.y = ScreenHeight / 2 - ScreenHeight / 40;
	rect2.h = ScreenHeight / 20;
	rect2.w = 0;

	rectBackground.x = 0;
	rectBackground.y = 0;
	rectBackground.w = ScreenWidth;
	rectBackground.h = ScreenHeight;
}

void LoadingState::setPercentage(int percentage)
{
	this->percentage = percentage;
}

void LoadingState::cleanup() 
{
}

void LoadingState::pause() 
{
}

void LoadingState::resume() 
{
}

void LoadingState::handleEvents(SDL_Event mainEvent) 
{	
}

void LoadingState::update(double dt) 
{
}

void LoadingState::draw() 
{	
	rect2.w = ((ScreenWidth / 3) / 100) * this->percentage;

	//Background
	GameStateManager::Instance()->sdlInitializer->drawTexture(textBackground, &rectBackground, NULL);
	
	//Loadingbar
	GameStateManager::Instance()->sdlInitializer->drawTexture(text1, &rect1, NULL);
	GameStateManager::Instance()->sdlInitializer->drawTexture(text2, &rect2, NULL);
	
	//Loading text
	
	GameStateManager::Instance()->sdlInitializer->drawText(std::string("Loading game"), ScreenWidth / 2 - 100, (ScreenHeight / 2) - (ScreenHeight / 30) - 100, 200, 50);

	//Procent text
	GameStateManager::Instance()->sdlInitializer->drawText(std::string(std::to_string(this->percentage) + " %"), ScreenWidth / 2 - 25, ScreenHeight / 2 - ScreenHeight / 30, 50, 50);
}

LoadingState::~LoadingState(void)
{
	//delete camera;
	//delete mec;
	//delete mapLoader;
	//TODO : DELETE MORE
	//delete text1/ text2
}