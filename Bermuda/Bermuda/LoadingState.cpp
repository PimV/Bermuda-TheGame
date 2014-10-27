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

	/*
	//Create MainentityContainer
	mec = new MainEntityContainer();
	//Create map loader and load the map
	mapLoader = new MapLoader(this->gsm, mec);
	mapLoader->loadMap();
	//Create new Camera
	camera = new Camera(0, 0, ScreenWidth, ScreenHeight, mapLoader->getMapWidth(), mapLoader->getMapHeight());
	//Start play music
	SoundLoader::Instance()->playGameMusic();
	//Create new Player
	p = new Player(1, 3, mapLoader->getStartPosX(), mapLoader->getStartPosY(), mapLoader->getChunkSize(), camera, gsm, mec);
	*/
}

void LoadingState::setPlayState(PlayState* playState)
{
	this->playState = playState;
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
