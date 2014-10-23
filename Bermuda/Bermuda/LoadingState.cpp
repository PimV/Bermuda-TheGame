#include "LoadingState.h"
#include <iostream>

LoadingState LoadingState::m_LoadingState;

LoadingState::LoadingState()
{
}

void LoadingState::init(GameStateManager *gsm) 
{
	this->gsm = gsm;
	this->i = 0;
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
	std::cout << "LOADING: " << this->i << std::endl;
	i++;
}

void LoadingState::draw() 
{
}


LoadingState::~LoadingState()
{
}
