#include "LoadingState.h"
#include "GameStateManager.h"
#include <iostream>

LoadingState LoadingState::m_LoadingState;

LoadingState::LoadingState(void)
{
}

void LoadingState::init(GameStateManager *gsm) {
	this->gsm = gsm;

	text1 = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "loading_bar_grey.bmp").c_str());
	text2 = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "loading_bar_green.bmp").c_str());

	rect1.x = 300;
	rect1.y = 300;
	rect1.h = 50;
	rect1.w = 500;

	rect2.x = 300;
	rect2.y = 300;
	rect2.h = 50;
	rect2.w = 0;
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
	rect2.w = this->percentage * 5;

	GameStateManager::Instance()->sdlInitializer->drawTexture(text1, &rect1, NULL);
	GameStateManager::Instance()->sdlInitializer->drawTexture(text2, &rect2, NULL);
	
	GameStateManager::Instance()->sdlInitializer->drawText(std::string(std::to_string(this->percentage) + " %"), 525, 305, 50, 50);
}

LoadingState::~LoadingState(void)
{
	//delete camera;
	//delete mec;
	//delete mapLoader;
	//TODO : DELETE MORE
	//delete text1/ text2
}